module mod_vicsek
    use mod_canvas
    implicit none

contains

    ! Initializes the Vicsek Fractal pattern.
    ! Defines a bounding square that perfectly fits the screen size and starts the recursive generation.
    subroutine init_vicsek(depth)
        integer, intent(in) :: depth
        real :: side, center_x, center_y, min_dim

        min_dim = min(real(pw), real(ph))
        side = min_dim
        center_x = real(pw) / 2.0
        center_y = real(ph) / 2.0

        call vicsek(center_x - side/2.0, center_y - side/2.0, side, depth)
    end subroutine init_vicsek

    ! Recursively splits and draws the Vicsek "Quadric Cross" fractal.
    ! Subdivides the area into 9 grid squares and recurses only into the 4 corners and the center.
    recursive subroutine vicsek(x, y, s, d)
        real, intent(in) :: x, y, s
        integer, intent(in) :: d
        real :: s3

        if (d == 0) then
            ! Draw a square box
            call draw_line(x, y, x+s, y)
            call draw_line(x+s, y, x+s, y+s)
            call draw_line(x+s, y+s, x, y+s)
            call draw_line(x, y+s, x, y)
        else
            s3 = s / 3.0
            
            ! Cross pattern (Vicsek): top, bottom, left, right, center
            call vicsek(x + s3, y, s3, d-1)         ! Top
            call vicsek(x + s3, y + 2.0*s3, s3, d-1)! Bottom
            call vicsek(x, y + s3, s3, d-1)         ! Left
            call vicsek(x + 2.0*s3, y + s3, s3, d-1)! Right
            call vicsek(x + s3, y + s3, s3, d-1)    ! Center
        end if
    end subroutine vicsek

end module mod_vicsek
