/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 3;        /* border pixel of windows */
static const int gappx                = 10;        /* gaps between windows */
static const unsigned int snap        = 0;        /* snap pixel */
static const int swallowfloating      = 0;        /* 1 means swallow floating windows by default */
static const int showbar              = 0;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const char *fonts[]            = { "IBM Plex Mono:size=11" };
static const char dmenufont[]         = "IBM Plex Mono:size=11";
static const char col_dark_grey[]     = "#030303";
static const char col_red[]           = "#ff009e";
static const char col_white[]         = "#ffffff";
static const char *colors[][3]      = {
	/*               fg                  bg                   border   */
	[SchemeNorm] = { col_white,          col_dark_grey,       col_dark_grey },
	[SchemeSel]  = { col_red,            col_dark_grey,       col_white },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance         title      tags mask     iscentered   isfloating   monitor */
	{ "st-256color",    "start",         NULL,      1,            0,           0,            0 },
	{ "st-256color",    "files",         NULL,      1 << 2,       0,           0,            0 },
	{ "st-256color",    "coms",          NULL,      1 << 3,       0,           0,            0 },
	{ "st-256color",    "calc",          NULL,      0,            1,           1,           -1 },
	{ "st-256color",    "popterm",       NULL,      0,            1,           1,           -1 },
	{ "qutebrowser",    NULL,            NULL,      1 << 1,       0,           0,            0 },
	{ "firefox",        NULL,            NULL,      1 << 1,       0,           0,            0 },
	{ "Steam",          NULL,            NULL,      1 << 4,       0,           0,            0 },
	{ "Spotify",        NULL,            NULL,      1 << 2,       0,           0,            1 },
	{ "discord",        NULL,            NULL,      1,            0,           0,            1 },
	{ "obs",            "obs",           NULL,      1 << 3,       0,           0,            1 },
	{ "Pavucontrol",    "pavucontrol",   NULL,      0,            1,           1,           -1 },
	{ "Gcolor2",        NULL,            NULL,      0,            1,           1,           -1 },
	{ "Dino",           "dino",          NULL,      1 << 4,       0,           0,            1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]              = { "st", "-n", "popterm", "-e", "decency_fzf_run", NULL };
static const char *termcmd[]               = { "st", NULL };
static const char *poptermcmd[]            = { "st", "-n", "popterm", "-g", "90x30", NULL };
static const char *scrupscreencmd[]        = { "scrup_screen", "1", NULL };
static const char *upscrupcmd[]            = { "upscrup", NULL };
static const char *scrupscreenpngcmd[]     = { "scrup_screen_png", "1", NULL };
static const char *scrupcmd[]              = { "scrup", NULL };
static const char *togglevpncmd[]          = { "st", "-n", "popterm", "-e", "fzf_wgc", NULL };
static const char *suspendcmd[]            = { "sudo", "systemctl", "suspend", NULL };
static const char *mutemiccmd[]            = { "mm", NULL };
static const char *mutecheckmiccmd[]       = { "mmm", NULL };
static const char *pavucontrolcmd[]        = { "pavucontrol", NULL };
static const char *calccmd[]               = { "st", "-n", "calc", "-e", "calc", NULL };
static const char *timecmd[]               = { "timepop", NULL };
static const char *steamcmd[]              = { "steam", NULL };
static const char *discordcmd[]            = { "discord-canary", NULL };
static const char *browsercmd[]            = { "qutebrowser", NULL };
static const char *geminicmd[]             = { "st", "-e", "amfora", "friendo.monster", NULL };
static const char *filemanagercmd[]        = { "st", "-e", "nnn", "-R", NULL };
static const char *clipboardcmd[]          = { "clipmenu", NULL };
static const char *colourpickercmd[]       = { "gcolor2", NULL };
static const char *togglecompositorcmd[]   = { "togglecompositor", NULL };
static const char *toggleresolutioncmd[]   = { "toggleresolution", NULL };
static const char *togglemonitorinputcmd[] = { "togglemonitorinput", NULL };
static const char *switchvolup[]           =  { "pactl", "set-source-volume", "alsa_input.pci-0000_00_1f.3.analog-stereo", "+2%", NULL };
static const char *switchvoldown[]         =  { "pactl", "set-source-volume", "alsa_input.pci-0000_00_1f.3.analog-stereo", "-2%", NULL };
static const char *passwordcmd[]           = { "st", "-n", "popterm", "-e", "fzf_pass", NULL };
static const char *emojicmd[]              = { "st", "-n", "popterm", "-e", "fzf_emoji", NULL };
static const char *dpopcmd[]               = { "st", "-n", "popterm", "-e", "fzf_pop", NULL };
static const char *ymenucmd[]              = { "st", "-n", "popterm", "-e", "fzf_youtube", NULL };
static const char *musicplay[]             = { "playerctl", "play-pause", NULL };
static const char *musicprev[]             = { "playerctl", "previous", NULL };
static const char *musicnext[]             = { "playerctl", "next", NULL };
static const char *volup[]                 = { "applicationvolume", "+5", NULL };
static const char *voldown[]               = { "applicationvolume", "-5", NULL };
static const char *plexvolup[]             = { "plexvolumeqb", "+5", NULL };
static const char *plexvoldown[]           = { "plexvolumeqb", "-5", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_space,                   spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return,                  spawn,          {.v = poptermcmd } },
	{ MODKEY,                       XK_f,                       spawn,          {.v = scrupscreencmd } },
	{ MODKEY|ControlMask,           XK_f,                       spawn,          {.v = upscrupcmd } },
	{ MODKEY|Mod1Mask,              XK_f,                       spawn,          {.v = scrupscreenpngcmd } },
	{ MODKEY|ShiftMask,             XK_f,                       spawn,          {.v = scrupcmd } },
	{ MODKEY|ShiftMask,             XK_n,                       spawn,          {.v = togglevpncmd } },
	{ MODKEY,                       XK_BackSpace,               spawn,          {.v = suspendcmd } },
	{ MODKEY|ShiftMask,             XK_s,                       spawn,          {.v = mutemiccmd } },
	{ MODKEY|ControlMask,           XK_s,                       spawn,          {.v = mutecheckmiccmd } },
	{ MODKEY|ShiftMask,             XK_i,                       spawn,          {.v = pavucontrolcmd } },
	{ MODKEY,                       XK_c,                       spawn,          {.v = calccmd } },
	{ MODKEY,                       XK_p,                       spawn,          {.v = timecmd } },
	{ MODKEY,                       XK_y,                       spawn,          {.v = steamcmd } },
	{ MODKEY,                       XK_o,                       spawn,          {.v = discordcmd } },
	{ MODKEY,                       XK_u,                       spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_s,                       spawn,          {.v = geminicmd } },
	{ MODKEY,                       XK_r,                       spawn,          {.v = filemanagercmd } },
	{ MODKEY,                       XK_v,                       spawn,          {.v = clipboardcmd } },
	{ MODKEY,                       XK_z,                       spawn,          {.v = colourpickercmd } },
	{ MODKEY|ShiftMask,             XK_c,                       spawn,          {.v = togglecompositorcmd } },
	{ MODKEY|ControlMask,           XK_c,                       spawn,          {.v = toggleresolutioncmd } },
	{ MODKEY|ShiftMask,             XK_m,                       spawn,          {.v = togglemonitorinputcmd } },
	{ MODKEY,                       XK_bracketright,            spawn,          {.v = switchvolup } },
	{ MODKEY,                       XK_bracketleft,             spawn,          {.v = switchvoldown } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = passwordcmd } },
	{ MODKEY,                       XK_e,                       spawn,          {.v = emojicmd } },
	{ MODKEY|ShiftMask,             XK_p,                       spawn,          {.v = dpopcmd } },
	{ MODKEY|ShiftMask,             XK_y,                       spawn,          {.v = ymenucmd } },
	{ 0,                            XF86XK_AudioPlay,           spawn,          {.v = musicplay } },
	{ 0,                            XF86XK_AudioPrev,           spawn,          {.v = musicprev } },
	{ 0,                            XF86XK_AudioNext,           spawn,          {.v = musicnext } },
	{ MODKEY,                       XK_equal,                   spawn,          {.v = volup } },
	{ MODKEY,                       XK_minus,                   spawn,          {.v = voldown } },
	{ MODKEY|ShiftMask,             XK_equal,                   spawn,          {.v = plexvolup } },
	{ MODKEY|ShiftMask,             XK_minus,                   spawn,          {.v = plexvoldown } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,                       movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                       movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,                       setmfact,       {.f = -0.001} },
	{ MODKEY|ControlMask,           XK_l,                       setmfact,       {.f = +0.001} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_Escape,                  view,           {0} },
	{ MODKEY,                       XK_w,                       killclient,     {0} },
	{ MODKEY,                       XK_m,                       setlayout,      {0} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,                       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l,                       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,                       tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_period,                  setcentered,    {0} },
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
