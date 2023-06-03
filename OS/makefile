GPPPARAMS=-m32 -Iinclude -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-stack-protector -Wno-write-strings
ASPARAMS= --32
LDPARAMS= -m elf_i386 

object= Obj/loader.o \
	Obj/drivers/driver.o \
        Obj/gdt.o \
        Obj/hardwareCommunication/interrupts.o \
        Obj/hardwareCommunication/pci.o \
        Obj/drivers/mouse.o \
        Obj/drivers/keyboard.o \
        Obj/hardwareCommunication/port.o \
        Obj/GUI/desktop.o \
	Obj/hardwareCommunication/interruptstubs.o \
	Obj/drivers/vga.o \
	Obj/GUI/widget.o \
	Obj/kernel.o \
	
run : mykernel.iso
	  (killall VirtualBox && sleep 1) || true
	  VirtualBox --startvm "mundix" &

Obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(GPPPARAMS) -o $@ -c $<
	
Obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<
	
mykernel.bin: linker.ld $(object)
	ld $(LDPARAMS) -T $< -o $@ $(object)
install: mykernel.bin
	sudo cp $< /boot/mykernel.bin
	
mykernel.iso : mykernel.bin 
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set Timeout=0'               	> iso/boot/grub/grub.cfg
	echo 'set default=0'               	>> iso/boot/grub/grub.cfg
	echo ''                            	>> iso/boot/grub/grub.cfg
	echo 'menuentry "mundix"{'         	>> iso/boot/grub/grub.cfg
	echo ' multiboot /boot/mykernel.bin' 	>> iso/boot/grub/grub.cfg
	echo ' boot' 				>> iso/boot/grub/grub.cfg
	echo ' }' 				>> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

	
.PHONY:clean
clean:
	rm -rf Obj mykernel.bin mykernel.iso
     
	
	
