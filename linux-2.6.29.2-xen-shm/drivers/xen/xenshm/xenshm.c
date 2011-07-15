/*
 * xenshm.c
 *
 *  Created on: Jul 25, 2009
 *      Author: chris
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <xen/xenbus.h>
#include "xenshm.h"

MODULE_LICENSE("GPL");

static int xenshm_init(void) {

	printk(KERN_ALERT "Loading...\n");

	major = register_chrdev(0, DEVICE_NAME, &xenshm_fops);

	if (major < 0) {
		printk("Registering the character device failed with %d\n", major);
		return major;
	}
	printk("I was assigned major number %d.\n", major);

	printk(KERN_ALERT "Loaded.\n");
	return 0;
}

static void xenshm_exit(void) {
	printk(KERN_ALERT "Unloading...\n");

	/* Unregister the device */
	unregister_chrdev(major, DEVICE_NAME);

printk(KERN_ALERT "Unloaded...\n");
}

static int xenshm_ioctl(struct inode *inode, struct file *filp,
		unsigned int cmd, unsigned long arg) {

	switch (cmd) {

	case PRINT_MSG:
		printk(KERN_ALERT "This is a message from the kernel!\n");
		break;

	default:
		return -ENOTTY;
	}
	return 0;
}

static int xenshm_mmap(struct file *filp, struct vm_area_struct *vma) {

	printk(KERN_ALERT "1\n");
	if (vma->vm_pgoff == 0) {

		long length = vma->vm_end - vma->vm_start;
		void* kmalloc_area;

		printk(KERN_ALERT "2\n");

		// check length - do not allow larger mappings than the number of pages allocated, PAGE_SIZE is from system

		if (length > MAX_PAGES * PAGE_SIZE) {
			return -EIO;
		} printk(KERN_ALERT "3\n");

		//get kernel mem
		kmalloc_area = kmalloc((MAX_PAGES + 2) * PAGE_SIZE, GFP_KERNEL);
		printk(KERN_ALERT "4\n");

		// map the whole physically contiguous area in one piece
		if (remap_pfn_range(vma, vma->vm_start, virt_to_phys( (void*) ((unsigned long) kmalloc_area)) >> PAGE_SHIFT, length, vma->vm_page_prot)) {
			printk("remap page range failed\n");
			return -ENXIO;
		}
		printk(KERN_ALERT "5\n");
		return 0;
	}
	return -EIO;
}

module_init( xenshm_init);
module_exit( xenshm_exit);
