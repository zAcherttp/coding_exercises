module mod_dragon
    use mod_canvas
    implicit none

    ! Pass states
    real :: glob_min_x, glob_max_x, glob_min_y, glob_max_y
    logical :: is_pass1

contains

    ! Initializes the Golden Dragon (Heighway Dragon) fractal rendering.
    ! Uses a two-pass mechanism to automatically detect shape boundary limits before drawing centered and uniformly scaled.
    subroutine init_dragon(depth)
        integer, intent(in) :: depth
        real :: scale_x, scale_y, scale, offset_x, offset_y
        
        ! Two-pass mechanism for Golden Dragon because it bounds unpredictably
        
        ! PASS 1: dry run to gather exact boundaries
        glob_min_x = 999999.0
        glob_max_x = -999999.0
        glob_min_y = 999999.0
        glob_max_y = -999999.0
        is_pass1 = .true.
        
        call dragon(0.0, 0.0, 1.0, 0.0, depth, 1)

        ! Calculate bounded scaling to perfectly fit window
        scale_x = real(pw - 1) / (glob_max_x - glob_min_x)
        scale_y = real(ph - 1) / (glob_max_y - glob_min_y)
        
        ! Use the minimum scale to preserve aspect ratio
        scale = min(scale_x, scale_y)
        
        ! Calculate centering offsets
        offset_x = (real(pw) - (glob_max_x - glob_min_x) * scale) / 2.0 - glob_min_x * scale
        offset_y = (real(ph) - (glob_max_y - glob_min_y) * scale) / 2.0 - glob_min_y * scale

        ! PASS 2: wet run drawing with offsets
        is_pass1 = .false.
        call dragon(0.0 * scale + offset_x, 0.0 * scale + offset_y, &
                    1.0 * scale + offset_x, 0.0 * scale + offset_y, depth, 1)
        
    end subroutine init_dragon

    ! Evaluates and draws folds iteratively for the Heighway Dragon curve.
    ! Discovers min/max sizes globally during Pass 1, and delegates actual line rendering to Pass 2 using offsets.
    recursive subroutine dragon(x1, y1, x2, y2, d, dir)
        real, intent(in) :: x1, y1, x2, y2
        integer, intent(in) :: d, dir
        real :: mx, my
        real :: dx, dy

        ! Record bounds in pass 1
        if (is_pass1) then
            if (min(x1, x2) < glob_min_x) glob_min_x = min(x1, x2)
            if (max(x1, x2) > glob_max_x) glob_max_x = max(x1, x2)
            if (min(y1, y2) < glob_min_y) glob_min_y = min(y1, y2)
            if (max(y1, y2) > glob_max_y) glob_max_y = max(y1, y2)
        end if

        if (d == 0) then
            if (.not. is_pass1) then
                call draw_line(x1, y1, x2, y2)
            end if
        else
            ! Standard Heighway Dragon curve subdivision
            dx = x2 - x1
            dy = y2 - y1
            
            if (dir == 1) then
                mx = x1 + (dx - dy) / 2.0
                my = y1 + (dx + dy) / 2.0
            else
                mx = x1 + (dx + dy) / 2.0
                my = y1 - (dx - dy) / 2.0
            end if
            
            call dragon(x1, y1, mx, my, d - 1, 1)
            call dragon(mx, my, x2, y2, d - 1, -1)
        end if
    end subroutine dragon

end module mod_dragon
