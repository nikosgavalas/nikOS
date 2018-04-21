#ifndef _PIC_H_INCLUDED_
#define _PIC_H_INCLUDED_

void pic_init();

/* Send an acknowledgement to the pic every time an irq is handled */
void pic_ack();

#endif // _PIC_H_INCLUDED_
