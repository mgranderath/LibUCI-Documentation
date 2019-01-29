struct uci_context myconfig_ctx;
struct uci_package myconfig_pkg;

struct uci_package *myconfig_init_package(const char *config_fname) {
  myconfig_pkg = calloc(1, sizeof(struct myconfig_pkg));
  if (NULL == myconfig_ctx) {
    myconfig_ctx = uci_alloc_context();
  }
  if (myconfig_pkg) {
    // unload first before loading
    uci_unload(myconfig_ctx, myconfig_pkg);
    myconfig_pkg = NULL;
  }
  if (uci_load(myconfig_ctx, config_fname, &myconfig_pkg)) {
    uci_free_context(myconfig_ctx);
    myconfig_ctx = NULL;
    return NULL;
   }
   return myconfig_pkg;
}


void myconfig_free_package(void) {
  if (myconfig_ctx){
    if (myconfig_pkg) {
      uci_unload(myconfig_ctx, myconfig_pkg);
      myconfig_pkg = NULL;
    }
    uci_free_context(myconfig_ctx);
    myconfig_ctx = NULL;
  }
}

myconfig_init_package("easycwmp");
