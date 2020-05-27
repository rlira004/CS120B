
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/
static int cnt = 0;

void Ping()
{
    switch(ping_state)
    {
        case PInit:
            break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
               cnt ++;
                if (cnt == 1)
                    PORTB = (0x01 & PORTB);
                else
                    PORTB = (0x00 & PORTB);
            break;
        default:
            break;
    }
}
