program dynamic_triflake
    use mod_canvas
    use mod_koch
    use mod_vicsek
    use mod_dragon
    implicit none

    integer :: depth, choice

    call init_canvas()

    print *, "--- Fractal Renderer ---"
    print *, "Detected terminal size:", tw, "x", th
    print *, "Choose a Fractal: 1. Anti-Snowflake (Koch) | 2. Vicsek / Quadric Cross | 3. Golden Dragon"
    read(*, *) choice
    print *, "Enter Recursion Depth (4-6 usually best): "
    read(*, *) depth
    print *, "---------------------------------"

    select case(choice)
        case(1)
            call init_koch(depth)
        case(2)
            call init_vicsek(depth)
        case(3)
            call init_dragon(depth)
        case default
            print *, "Invalid choice."
            call clear_canvas()
            stop
    end select

    call render_canvas()

    call clear_canvas()
    deallocate(buffer)

end program dynamic_triflake