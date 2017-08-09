
#include "headers/important.h"


bool intro_main()
{
    
    if (get_time() == 0) {
            // Do something
    } else if (get_time() < 2 * SECOND) {
        //Do more things
    }
    
    
    if (key_down(KEY_A | KEY_B | KEY_START) || get_time() == 20 * SECOND)
    {
        return true;
    }
    
    inc_timer();
    return false;
}




