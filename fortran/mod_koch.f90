module mod_koch
    use mod_canvas
    implicit none

contains

    ! Sets up and triggers the Koch Anti-Snowflake generation.
    ! Calculates an equilateral triangle maximizing terminal bounds, then recurses each of its 3 sides.
    subroutine init_koch(depth)
        integer, intent(in) :: depth
        real :: side, center_x, center_y, x1, y1, x2, y2, x3, y3
        real :: min_dim

        ! Exact scaling - make the triangle touch the edges
        min_dim = min(real(pw), real(ph))
        side = min_dim
        center_x = real(pw) / 2.0
        center_y = real(ph) / 2.0

        x1 = center_x - (side / 2.0)
        y1 = center_y + (side * 0.288675)
        
        x2 = center_x + (side / 2.0)
        y2 = center_y + (side * 0.288675)
        
        x3 = center_x
        y3 = center_y - (side * 0.577350)

        call koch(x1, y1, x2, y2, depth)
        call koch(x2, y2, x3, y3, depth)
        call koch(x3, y3, x1, y1, depth)
    end subroutine init_koch

    ! Recursively draws a line applying the Koch curve rules.
    ! Splits the segment into thirds, replacing the middle third with two segments folding inward.
    recursive subroutine koch(kx1, ky1, kx5, ky5, d)
        real, intent(in) :: kx1, ky1, kx5, ky5
        integer, intent(in) :: d
        real :: kx2, ky2, kx3, ky3, kx4, ky4, dx, dy
        real, parameter :: cos60 = 0.5
        real, parameter :: sin60 = 0.8660254

        if (d == 0) then
            call draw_line(kx1, ky1, kx5, ky5)
        else
            dx = (kx5 - kx1) / 3.0
            dy = (ky5 - ky1) / 3.0
            
            kx2 = kx1 + dx
            ky2 = ky1 + dy
            
            kx4 = kx1 + 2.0 * dx
            ky4 = ky1 + 2.0 * dy
            
            kx3 = kx2 + dx * cos60 + dy * sin60
            ky3 = ky2 - dx * sin60 + dy * cos60
            
            call koch(kx1, ky1, kx2, ky2, d - 1)
            call koch(kx2, ky2, kx3, ky3, d - 1)
            call koch(kx3, ky3, kx4, ky4, d - 1)
            call koch(kx4, ky4, kx5, ky5, d - 1)
        end if
    end subroutine koch

end module mod_koch
