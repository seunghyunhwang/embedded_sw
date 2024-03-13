SHELL := /bin/bash
PRJ_DIR_PATH := /work/sw03
BUILDROOT_PATH := https://buildroot.org/downloads/buildroot-2023.02.1.tar.gz
KERNEL_PATH := https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.2.5.tar.xz
TOOLCHAIN_PATH := https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz
CROSS_COMPILE := toolchain/bin/aarch64-none-linux-gnu-
ARCH := arm64
CURRENT_TARGET :=

.PHONY : buildroot kernel

all: buildroot-download buildroot-config buildroot kernel-download toolchain-download kernel-config kernel build-check

run:
	@qemu-system-aarch64 \
	-kernel $(PRJ_DIR_PATH)/linux/arch/arm64/boot/Image \
	-drive format=raw,file=$(PRJ_DIR_PATH)/buildroot/output/images/rootfs.ext4,if=virtio \
	-append "root=/dev/vda console=ttyAMA0 nokaslr" \
	-nographic -M virt \
	-cpu cortex-a72 \
	-m 2G \
	-smp 2
clean:
	$(eval CURRENT_TARGET := $@)
	@echo "Cleaning...";\
	rm -rf li* gc* bu* too*;\
	echo "Done"
buildroot-download:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/buildroot ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] start | tr '[:lower:]' '[:upper:]')"; \
		wget -q $(BUILDROOT_PATH);\
		tar xvf buildroot-2023.02.1.tar.gz\
		>/dev/null 2<&1;\
		mv buildroot-2023.02.1 buildroot;\
		echo "$(shell echo [$(CURRENT_TARGET)] Done | tr '[:lower:]' '[:upper:]')"; \
	fi
buildroot-config:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/buildroot/output/images/rootfs.ext4 ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] start | tr '[:lower:]' '[:upper:]')"; \
		cp /work/day03/buildroot/buildroot/.config $(PRJ_DIR_PATH)/buildroot/.config; \
		make olddefconfig -C $(PRJ_DIR_PATH)/buildroot | sed 's/^/[$(CURRENT_TARGET)] /' | tr '[:lower:]' '[:upper:]'; \
		echo "$(shell echo [$(CURRENT_TARGET)] Done | tr '[:lower:]' '[:upper:]')"; \
	fi

buildroot:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/buildroot/output/images/rootfs.ext4 ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] start | tr '[:lower:]' '[:upper:]')"; \
		make -j8 -C $(PRJ_DIR_PATH)/buildroot | sed 's/^/[$(CURRENT_TARGET)] /' | tr '[:lower:]' '[:upper:]'; \
		echo "$(shell echo [$(CURRENT_TARGET)] Done | tr '[:lower:]' '[:upper:]')"; \
	fi

kernel-download:
	$(eval CURRENT_TARGET := $@)
	@if [ -e linux ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] start | tr '[:lower:]' '[:upper:]')"; \
		wget -q $(KERNEL_PATH);\
		tar xvf linux-6.2.5.tar.xz\
		>/dev/null 2<&1;\
		mv linux-6.2.5 linux;\
		echo "$(shell echo [$(CURRENT_TARGET)] done | tr '[:lower:]' '[:upper:]')"; \
	fi
toolchain-download:	
	$(eval CURRENT_TARGET := $@)
	@if [ -e toolchain ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] start | tr '[:lower:]' '[:upper:]')"; \
		wget -q $(TOOLCHAIN_PATH);\
		echo "$(shell echo [$(CURRENT_TARGET)] 1/2 done | tr '[:lower:]' '[:upper:]')"; \
		tar xvf gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu.tar.xz \
		>/dev/null 2<&1;\
		mv gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu \
		toolchain;\
		echo "$(shell echo [$(CURRENT_TARGET)] 2/2 done | tr '[:lower:]' '[:upper:]')"; \
	fi
kernel-config:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/linux/arch/arm64/boot/Image ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] 1/3 start | tr '[:lower:]' '[:upper:]')"; \
		cp $(PRJ_DIR_PATH)/buildroot/board/qemu/aarch64-virt/linux.config \
		$(PRJ_DIR_PATH)/linux/arch/arm64/configs/qemu_defconfig;\
		echo "$(shell echo [$(CURRENT_TARGET)] 2/3 done | tr '[:lower:]' '[:upper:]')"; \
		((make qemu_defconfig ARCH=$(ARCH) \
		CROSS_COMPILE=$(PRJ_DIR_PATH)/$(CROSS_COMPILE) -C $(PRJ_DIR_PATH)/linux) | sed 's/^/[$(CURRENT_TARGET)] /' | tr '[:lower:]' '[:upper:]';\
 );\
		echo "$(shell echo [$(CURRENT_TARGET)] 3/3 done | tr '[:lower:]' '[:upper:]')"; \
	fi

kernel:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/linux/arch/arm64/boot/Image ]; then\
		echo -e -n "\033[43m"; \
		echo -n "[$(CURRENT_TARGET)] SKIPPED" | tr '[:lower:]' '[:upper:]'; \
		echo -e "\033[0m"; \
	else \
		echo "$(shell echo [$(CURRENT_TARGET)] 1/2 start | tr '[:lower:]' '[:upper:]')"; \
		((make -j8 ARCH=$(ARCH) \
		CROSS_COMPILE=$(PRJ_DIR_PATH)/$(CROSS_COMPILE) -C $(PRJ_DIR_PATH)/linux) | grep 'vmlinux\|Image') | sed 's/^/[$(CURRENT_TARGET)] /' | tr '[:lower:]' '[:upper:]';\
		echo "$(shell echo [$(CURRENT_TARGET)] 2/2 done | tr '[:lower:]' '[:upper:]')"; \
	fi
build-check:
	$(eval CURRENT_TARGET := $@)
	@if [ -e $(PRJ_DIR_PATH)/linux/arch/arm64/boot/Image ]; then \
		echo -e -n "\033[42m"; \
		echo -n "$(shell echo [$(CURRENT_TARGET)] SUCCESS | tr '[:lower:]' '[:upper:]')"; \
		echo -e "\033[0m"; \
	else \
		echo -e -n "\033[41m"; \
		echo -n "$(shell echo [$(CURRENT_TARGET)] FAILURE | tr '[:lower:]' '[:upper:]')"; \
		echo -e "\033[0m"; \
	fi \


