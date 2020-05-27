//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/
static int detCnt = 0;
void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            if(~PINA > 0x00)
                detect_eq_state = DEQDetect;
            else
                detect_eq_state = DEQInit;
            break;
        case DEQDetect:
             if(detCnt == 2)
                detect_eq_state = DEQInit;
            else
                detect_eq_state = DEQDetect;
            break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            PORTB = (PORTB = 0x00) << 2;
            break;
        case DEQDetect:
            detCnt++;
             PORTB = (0x02 & PORTB);
            break;
        default:
            break;
    }
}
