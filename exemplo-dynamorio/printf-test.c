#include "../include/dr_api.h"
#include "../ext/include/drmgr.h"
#include "../ext/include/drwrap.h"
#include "../ext/include/drutil.h"
#include "../ext/include/drreg.h"


//gcc -fPIC -shared -lgcc -DLINUX -DX86_32 -I$DYNAMORIO_HOME/include my-client.c

static void event_exit(void);

static void
wrap_pre_printf(void *wrapcxt, OUT void **user_data)
{

}

DR_EXPORT void 
module_load_event(void *drcontext, const module_data_t *mod, bool loaded)
{
    app_pc towrap = (app_pc) dr_get_proc_address(mod->handle, "printf");
    if (towrap != NULL) {
        bool ok = drwrap_wrap(towrap, wrap_pre_printf, NULL);
        if (!ok) {
            dr_fprintf(STDERR, "Couldn’t wrap printf\n");
            DR_ASSERT(ok);
        }
    }


}

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[])
{
    /* empty client */
    dr_set_client_name("DynamoRIO Sample Client 'empty'", "http://dynamorio.org/issues");
    DynamoRIO_extension();
    drmgr_init();
    drwrap_init();
    dr_register_exit_event(event_exit);
    drmgr_register_module_load_event(module_load_event);
}

static void
event_exit(void)
{
    drwrap_exit();
    drmgr_exit();
}
