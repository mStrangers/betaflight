#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "cli/settings.h"
#include "flight/mixer.h"

#include "cms/cms.h"
#include "cms/cms_types.h"
#include "cms/cms_menu_altlim.h"

#include "config/feature.h"

#include "config/config.h"





static uint16_t cmsx_alt_cutoff_lim; // Cutt off altitude
static uint16_t cmsx_alt_buffer_lim; // Buffer size

static const void *cmsx_Altlim_OnEnter(displayPort_t *pDisp)
{
    UNUSED(pDisp);

    cmsx_alt_cutoff_lim = mixerConfig()->alt_cutoff_lim;
    cmsx_alt_buffer_lim = mixerConfig()->alt_buffer_lim;

    return NULL;
}

static const void *cmsx_Altlim_OnExit(displayPort_t *pDisp, const OSD_Entry *self)
{
    UNUSED(pDisp);
    UNUSED(self);

    mixerConfigMutable()->alt_cutoff_lim = cmsx_alt_cutoff_lim ;
    mixerConfigMutable()->alt_buffer_lim = cmsx_alt_buffer_lim ;


    return NULL;
}

static const OSD_Entry cmsx_menuAltlimEntries[] =
{
    { "-- ALT LIMIT --",  OME_Label, NULL, NULL },
    { "CUTOFF",    OME_UINT16,NULL, &(OSD_UINT16_t){ &cmsx_alt_cutoff_lim, 0, 1000, 1 } },
    { "BUFFER",    OME_UINT16,NULL, &(OSD_UINT16_t){ &cmsx_alt_buffer_lim, 0, 1000, 1 } },
    { "BACK", OME_Back, NULL, NULL },
    { NULL, OME_END, NULL, NULL }
};

CMS_Menu cmsx_menuAltlim = {
#ifdef CMS_MENU_DEBUG
    .GUARD_text = "MENUALT",
    .GUARD_type = OME_MENU,
#endif
    .onEnter = cmsx_Altlim_OnEnter,
    .onExit = cmsx_Altlim_OnExit,
    .onDisplayUpdate = NULL,
    .entries = cmsx_menuAltlimEntries
};