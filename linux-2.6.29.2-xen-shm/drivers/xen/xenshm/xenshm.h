//defines
#define DEVICE_NAME "xenshm"
#define MAX_PAGES 4

//IOCTL commands
#define PRINT_MSG 0

//static vars
static int major = 0;

//functions
static int xenshm_ioctl(struct inode *inode, struct file *filp,unsigned int cmd, unsigned long arg );
static int xenshm_mmap(struct file *filp, struct vm_area_struct *vma);

//structs
static struct file_operations xenshm_fops = {
    owner:    THIS_MODULE,
    read:     NULL,
    write:    NULL,
    ioctl:    xenshm_ioctl,
    open:     NULL,
    release:  NULL,
    mmap:	  xenshm_mmap,
};

