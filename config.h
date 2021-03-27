/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 2;        /* border pixel of windows */
static const int gappx                = 3;        /* gaps between windows */
static const unsigned int snap        = 0;        /* snap pixel */
static const int swallowfloating      = 0;        /* 1 means swallow floating windows by default */
static const int showbar              = 0;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const char *fonts[]            = { "FiraCode-Regular:size=15" };
static const char dmenufont[]         = "FiraCode-Regular:size=15";
static const char col_cyan[]          = "#005577";
static const char col_dark_grey[]     = "#030303";
static const char col_red[]           = "#3ae02b";
static const char col_white[]         = "#ffffff";
static const char *colors[][3]      = {
	/*               fg                  bg                   border   */
	[SchemeNorm] = { col_white,          col_dark_grey,       col_dark_grey },
	[SchemeSel]  = { col_red,            col_dark_grey,       col_white },
};

/* tagging */
static const char *tags[] = { "main", "code", "book", "misc" };

static const Rule rules[] = {
	/* class     instance  title           tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,          1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          0,          -1,        -1 },
	{ "st-256color","popterm",NULL,        0,         1,          1,          1,           0,        -1 },
	{ "st",      "media",  NULL,           3 << 3,         0,          0,          1,           0,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          0,          1,           0,        -1 },
	{ "Gcolor2", NULL,     NULL,           0,         1,          1,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]               = { "st", NULL };
static const char *poptermcmd[]            = { "st", "-n", "popterm", "-g", "90x30", NULL };
static const char *ytaudio[]               = { "st", "-n", "media", "-e", "ytfzf", "-tml", NULL };
static const char *ytvideo[]               = { "st", "-n", "media", "-e", "ytfzf", "-tl", NULL };
static const char *suspendcmd[]            = { "sudo", "systemctl", "suspend", NULL };
static const char *browsercmd[]            = { "firefox", NULL };
static const char *filemanagercmd[]        = { "st", "-e", "ranger", NULL };
static const char *colourpickercmd[]       = { "gcolor2", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_space,                   spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return,                  spawn,          {.v = poptermcmd } },
	{ MODKEY,                       XK_BackSpace,               spawn,          {.v = suspendcmd } },
	{ MODKEY,                       XK_f,                       spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_r,                       spawn,          {.v = filemanagercmd } },
	{ MODKEY|ShiftMask,             XK_y,                       spawn,          {.v = ytaudio } },
	{ MODKEY,                       XK_y,                       spawn,          {.v = ytvideo } },
	{ MODKEY|ShiftMask,             XK_z,                       spawn,          {.v = colourpickercmd } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,                       movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                       movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_Escape,                  view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                       killclient,     {0} },
	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,                       tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,                  setcentered,    {0} },
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
