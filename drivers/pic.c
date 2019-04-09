#include <drivers/pic.h>
#include <lib/asm.h>

#define MASTER_PIC_CMD_PORT 0x20
#define MASTER_PIC_DATA_PORT 0x21
#define SLAVE_PIC_CMD_PORT 0xA0
#define SLAVE_PIC_DATA_PORT 0xA1

#define PIC_ACK 0x20

/* Master PIC */
#define IRQ_TIMER 0x01
#define IRQ_KEYB 0x02
#define IRQ_PIC2 0x04
#define IRQ_COM_2 0x08
#define IRQ_COM_1 0x10
#define IRQ_LPT_2 0x20
#define IRQ_FLOPPY 0x40
#define IRQ_LPT_1 0x80

/* Slave PIC */
#define IRQ_RTC 0x01
#define IRQ_GEN_IO1 0x02
#define IRQ_GEN_IO2 0x04
#define IRQ_GEN_IO3 0x08
#define IRQ_GEN_IO4 0x10
#define IRQ_COPROC 0x20
#define IRQ_IDE_BUS_1 0x40
#define IRQ_IDE_BUS_2 0x80

/* See: https://www-s.acm.illinois.edu/sigops/2007/roll_your_own/i386/irq.html
 * and https://wiki.osdev.org/PIC
 */
void pic_configure() {
    /* Level Triggered, Master/Slave config, w/ICW4 */
    outb(MASTER_PIC_CMD_PORT, 0x11);
    outb(SLAVE_PIC_CMD_PORT, 0x11);

    /* Offset into the IDT (remap) */
    outb(MASTER_PIC_DATA_PORT, 0x20);
    outb(SLAVE_PIC_DATA_PORT, 0x28);

    /* 0 -> IR line connected to peripheral, 1 -> IR line connected to slave */
    outb(MASTER_PIC_DATA_PORT, 0x04);
    /* IRQ on master this slave is connected to */
    outb(SLAVE_PIC_DATA_PORT, 0x02);

    /* Master PIC, 8086/88 Mode */
    outb(MASTER_PIC_DATA_PORT, 0x05);
    /* Slave PIC, 8086/88 Mode */
    outb(SLAVE_PIC_DATA_PORT, 0x01);
}

void pic_apply_masks(unsigned char master_mask, unsigned char slave_mask) {
    outb(MASTER_PIC_DATA_PORT, ~master_mask);
    outb(SLAVE_PIC_DATA_PORT, ~slave_mask);
}

void pic_init() {
    pic_configure();
    pic_apply_masks(IRQ_KEYB, 0);
    asm_enable_interrupts();
}

void pic_ack() {
    outb(MASTER_PIC_CMD_PORT, PIC_ACK);
    outb(SLAVE_PIC_CMD_PORT, PIC_ACK);
}
