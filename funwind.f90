module funwind

        interface
           subroutine show_backtrace() bind(C,name="show_backtrace")
           end subroutine
        end interface

end
