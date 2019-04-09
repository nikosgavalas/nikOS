#include <descriptors/gdt.h>
#include <descriptors/idt.h>
#include <lib/asm.h>

#include <interrupt/asm_int_handlers.h>

/* Array of pointers to the handler functions declared
 * in asm_int_handlers.h
 */
void (*asm_int_handlers[256])() = {
    asm_int_handler_0,   asm_int_handler_1,   asm_int_handler_2,
    asm_int_handler_3,   asm_int_handler_4,   asm_int_handler_5,
    asm_int_handler_6,   asm_int_handler_7,   asm_int_handler_8,
    asm_int_handler_9,   asm_int_handler_10,  asm_int_handler_11,
    asm_int_handler_12,  asm_int_handler_13,  asm_int_handler_14,
    asm_int_handler_15,  asm_int_handler_16,  asm_int_handler_17,
    asm_int_handler_18,  asm_int_handler_19,  asm_int_handler_20,
    asm_int_handler_21,  asm_int_handler_22,  asm_int_handler_23,
    asm_int_handler_24,  asm_int_handler_25,  asm_int_handler_26,
    asm_int_handler_27,  asm_int_handler_28,  asm_int_handler_29,
    asm_int_handler_30,  asm_int_handler_31,  asm_int_handler_32,
    asm_int_handler_33,  asm_int_handler_34,  asm_int_handler_35,
    asm_int_handler_36,  asm_int_handler_37,  asm_int_handler_38,
    asm_int_handler_39,  asm_int_handler_40,  asm_int_handler_41,
    asm_int_handler_42,  asm_int_handler_43,  asm_int_handler_44,
    asm_int_handler_45,  asm_int_handler_46,  asm_int_handler_47,
    asm_int_handler_48,  asm_int_handler_49,  asm_int_handler_50,
    asm_int_handler_51,  asm_int_handler_52,  asm_int_handler_53,
    asm_int_handler_54,  asm_int_handler_55,  asm_int_handler_56,
    asm_int_handler_57,  asm_int_handler_58,  asm_int_handler_59,
    asm_int_handler_60,  asm_int_handler_61,  asm_int_handler_62,
    asm_int_handler_63,  asm_int_handler_64,  asm_int_handler_65,
    asm_int_handler_66,  asm_int_handler_67,  asm_int_handler_68,
    asm_int_handler_69,  asm_int_handler_70,  asm_int_handler_71,
    asm_int_handler_72,  asm_int_handler_73,  asm_int_handler_74,
    asm_int_handler_75,  asm_int_handler_76,  asm_int_handler_77,
    asm_int_handler_78,  asm_int_handler_79,  asm_int_handler_80,
    asm_int_handler_81,  asm_int_handler_82,  asm_int_handler_83,
    asm_int_handler_84,  asm_int_handler_85,  asm_int_handler_86,
    asm_int_handler_87,  asm_int_handler_88,  asm_int_handler_89,
    asm_int_handler_90,  asm_int_handler_91,  asm_int_handler_92,
    asm_int_handler_93,  asm_int_handler_94,  asm_int_handler_95,
    asm_int_handler_96,  asm_int_handler_97,  asm_int_handler_98,
    asm_int_handler_99,  asm_int_handler_100, asm_int_handler_101,
    asm_int_handler_102, asm_int_handler_103, asm_int_handler_104,
    asm_int_handler_105, asm_int_handler_106, asm_int_handler_107,
    asm_int_handler_108, asm_int_handler_109, asm_int_handler_110,
    asm_int_handler_111, asm_int_handler_112, asm_int_handler_113,
    asm_int_handler_114, asm_int_handler_115, asm_int_handler_116,
    asm_int_handler_117, asm_int_handler_118, asm_int_handler_119,
    asm_int_handler_120, asm_int_handler_121, asm_int_handler_122,
    asm_int_handler_123, asm_int_handler_124, asm_int_handler_125,
    asm_int_handler_126, asm_int_handler_127, asm_int_handler_128,
    asm_int_handler_129, asm_int_handler_130, asm_int_handler_131,
    asm_int_handler_132, asm_int_handler_133, asm_int_handler_134,
    asm_int_handler_135, asm_int_handler_136, asm_int_handler_137,
    asm_int_handler_138, asm_int_handler_139, asm_int_handler_140,
    asm_int_handler_141, asm_int_handler_142, asm_int_handler_143,
    asm_int_handler_144, asm_int_handler_145, asm_int_handler_146,
    asm_int_handler_147, asm_int_handler_148, asm_int_handler_149,
    asm_int_handler_150, asm_int_handler_151, asm_int_handler_152,
    asm_int_handler_153, asm_int_handler_154, asm_int_handler_155,
    asm_int_handler_156, asm_int_handler_157, asm_int_handler_158,
    asm_int_handler_159, asm_int_handler_160, asm_int_handler_161,
    asm_int_handler_162, asm_int_handler_163, asm_int_handler_164,
    asm_int_handler_165, asm_int_handler_166, asm_int_handler_167,
    asm_int_handler_168, asm_int_handler_169, asm_int_handler_170,
    asm_int_handler_171, asm_int_handler_172, asm_int_handler_173,
    asm_int_handler_174, asm_int_handler_175, asm_int_handler_176,
    asm_int_handler_177, asm_int_handler_178, asm_int_handler_179,
    asm_int_handler_180, asm_int_handler_181, asm_int_handler_182,
    asm_int_handler_183, asm_int_handler_184, asm_int_handler_185,
    asm_int_handler_186, asm_int_handler_187, asm_int_handler_188,
    asm_int_handler_189, asm_int_handler_190, asm_int_handler_191,
    asm_int_handler_192, asm_int_handler_193, asm_int_handler_194,
    asm_int_handler_195, asm_int_handler_196, asm_int_handler_197,
    asm_int_handler_198, asm_int_handler_199, asm_int_handler_200,
    asm_int_handler_201, asm_int_handler_202, asm_int_handler_203,
    asm_int_handler_204, asm_int_handler_205, asm_int_handler_206,
    asm_int_handler_207, asm_int_handler_208, asm_int_handler_209,
    asm_int_handler_210, asm_int_handler_211, asm_int_handler_212,
    asm_int_handler_213, asm_int_handler_214, asm_int_handler_215,
    asm_int_handler_216, asm_int_handler_217, asm_int_handler_218,
    asm_int_handler_219, asm_int_handler_220, asm_int_handler_221,
    asm_int_handler_222, asm_int_handler_223, asm_int_handler_224,
    asm_int_handler_225, asm_int_handler_226, asm_int_handler_227,
    asm_int_handler_228, asm_int_handler_229, asm_int_handler_230,
    asm_int_handler_231, asm_int_handler_232, asm_int_handler_233,
    asm_int_handler_234, asm_int_handler_235, asm_int_handler_236,
    asm_int_handler_237, asm_int_handler_238, asm_int_handler_239,
    asm_int_handler_240, asm_int_handler_241, asm_int_handler_242,
    asm_int_handler_243, asm_int_handler_244, asm_int_handler_245,
    asm_int_handler_246, asm_int_handler_247, asm_int_handler_248,
    asm_int_handler_249, asm_int_handler_250, asm_int_handler_251,
    asm_int_handler_252, asm_int_handler_253, asm_int_handler_254,
    asm_int_handler_255};

/* https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_IA-32 */
struct idt_entry {
    unsigned short offset_low;
    unsigned short segment_selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short offset_high;
} __attribute__((packed));

/* https://wiki.osdev.org/Interrupt_Descriptor_Table#Loading.2FStoring */
struct idt_ptr {
    unsigned short size;
    unsigned int offset;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void init_idt_entry(unsigned char num, unsigned int offset,
                    unsigned short segment, unsigned char flags) {
    idt[num].offset_high = (unsigned short)((offset & 0xffff0000) >> 16);
    idt[num].offset_low = (unsigned short)(offset & 0x0000ffff);

    idt[num].segment_selector = segment;

    idt[num].zero = 0;
    idt[num].flags = flags;
}

void idt_install() {
    /* Flags = 1000 1110: Present = 1, DPL = 00 (Ring 0), S = 1 (interrupt gate)
     *                    Type = 1110 (32-bit interrupt gate)
     */
    for (unsigned int i = 0; i < 256; i++) {
        init_idt_entry((unsigned char)i, (unsigned int)asm_int_handlers[i],
                       SEGMENT_SELECTOR(CODE_SEG), 0b10001110);
    }

    idtp.size = (unsigned short)sizeof(idt) - 1;
    idtp.offset = (unsigned int)&idt;

    asm_load_idt((void *)&idtp);
}
