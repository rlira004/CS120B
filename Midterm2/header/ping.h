
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/
unsigned int cnt = 0;

void Ping()
{
    switch(ping_state)
    {
        case PInit:
            ping_state = PInit;
            break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
               //cnt ++;
               // if (cnt > 3) {
                    PORTB = 0x01;
                //    cnt = 0;
               // }
                //else
                  //  PORTB = (0x00 & PORTB);
            break;
        default:
            break;
    }
}
