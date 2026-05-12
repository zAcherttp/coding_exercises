module mod_canvas
    use iso_c_binding
    implicit none

    ! Global canvas state
    integer :: tw, th, pw, ph
    logical, allocatable :: buffer(:,:)

    interface
        subroutine get_terminal_size_c(rows, cols) bind(c, name="get_terminal_size")
            import :: c_int
            integer(c_int), intent(out) :: rows, cols
        end subroutine
    end interface

contains

    ! Initializes the global drawing canvas buffer.
    ! Fetches terminal size via C binding, scales to 2x4 braille pixel grid, and allocates logic array.
    subroutine init_canvas()
        integer(c_int) :: th_c, tw_c
        call get_terminal_size_c(th_c, tw_c)
        tw = tw_c
        th = th_c
        pw = tw * 2
        ph = th * 4
        allocate(buffer(0:pw-1, 0:ph-1))
        buffer = .false.
    ! Resets the drawing canvas.
    ! Sets all allocated pixels in the logical buffer back to .false.
    end subroutine init_canvas

    subroutine clear_canvas()
        if (allocated(buffer)) then
            buffer = .false.
        end if
    end subroutine clear_canvas

    ! Renders the logical buffer grid out to the terminal.
    ! Translates every 2x4 pixel block into a single UTF-8 Braille character mapping.
    subroutine render_canvas()
        integer :: cx, cy, bx, by, braille_val, bit_shift
        character(len=3) :: utf8_char

        do cy = 0, ph-1, 4
            do cx = 0, pw-1, 2
                braille_val = 0
                do by = 0, 3
                    do bx = 0, 1
                        if (buffer(cx + bx, cy + by)) then
                            if (by < 3) then
                                bit_shift = by + (bx * 3)
                            else
                                bit_shift = 6 + bx
                            end if
                            braille_val = ibset(braille_val, bit_shift)
                        end if
                    end do
                end do

                utf8_char(1:1) = char(226)
                utf8_char(2:2) = char(160 + ishft(braille_val, -6))
                utf8_char(3:3) = char(128 + iand(braille_val, 63))

                write(*, '(A)', advance='no') utf8_char
            end do
            write(*, *)
        end do
    end subroutine render_canvas

    ! Draws a straight line between two coordinates.
    ! Uses Bresenham's line algorithm to plot the continuous closest-pixel path in the buffer.
    subroutine draw_line(lx1, ly1, lx2, ly2)
        real, intent(in) :: lx1, ly1, lx2, ly2
        integer :: ix1, iy1, ix2, iy2
        integer :: d_x, d_y, sx, sy, err, e2
        
        ix1 = nint(lx1); iy1 = nint(ly1)
        ix2 = nint(lx2); iy2 = nint(ly2)
        
        d_x = abs(ix2 - ix1)
        d_y = abs(iy2 - iy1)
        if (ix1 < ix2) then; sx = 1; else; sx = -1; end if
        if (iy1 < iy2) then; sy = 1; else; sy = -1; end if
        err = d_x - d_y
        
        do
            if (ix1 >= 0 .and. ix1 < pw .and. iy1 >= 0 .and. iy1 < ph) then
                buffer(ix1, iy1) = .true.
            end if
            
            if (ix1 == ix2 .and. iy1 == iy2) exit
            
            e2 = 2 * err
            if (e2 > -d_y) then
                err = err - d_y
                ix1 = ix1 + sx
            end if
            if (e2 < d_x) then
                err = err + d_x
                iy1 = iy1 + sy
            end if
        end do
    end subroutine draw_line

    ! Draws a circle around a center point with a given radius.
    ! Uses Bresenham's circle algorithm to efficiently plot 8 symmetrical octants simultaneously.
    subroutine draw_circle(cx, cy, r)
        integer, intent(in) :: cx, cy, r
        integer :: x, y, err

        x = r
        y = 0
        err = 0

        do while (x >= y)
            call plot(cx + x, cy + y)
            call plot(cx + y, cy + x)
            call plot(cx - y, cy + x)
            call plot(cx - x, cy + y)
            call plot(cx - x, cy - y)
            call plot(cx - y, cy - x)
            call plot(cx + y, cy - x)
            call plot(cx + x, cy - y)

            if (err <= 0) then
                y = y + 1
                err = err + 2*y + 1
            endif
            if (err > 0) then
                x = x - 1
                err = err - 2*x + 1
            endif
        end do
    end subroutine draw_circle

    ! Safely plots a single pixel onto the buffer.
    ! Checks if the (x, y) coordinates fall within the allocated canvas resolution limits first.
    subroutine plot(x, y)
        integer, intent(in) :: x, y
        if (x >= 0 .and. x < pw .and. y >= 0 .and. y < ph) then
            buffer(x, y) = .true.
        end if
    end subroutine plot

end module mod_canvas
