/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-courier new-normal-r-normal-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#2F5B8B"; // Dark blue
static const char normbgcolor[]     = "#2F5B8B"; // Dark blue
static const char normfgcolor[]     = "#0DCEF8"; // Cyan
static const char selbordercolor[]  = "#879ECC"; // Dark bluish
static const char selbgcolor[]      = "#2F5B8B"; // Darker cyan
static const char selfgcolor[]      = "#ffffff"; // White
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1*System", "2*Devices", "3*IM", "4*Web" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY	Mod1Mask
#define MODKEY2	Mod5Mask	/* Alt Gr for left handed people */

static int modkeys[] = { MODKEY, MODKEY2 };

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *cmd_term[]  = { "st", NULL};
static const char *cmd_term2[]  = { "xterm", NULL};
static const char *cmd_term3[]  = { "terminator", "-b", NULL, NULL};
static const char *cmd_filemgr[]  = { "rox-filer", NULL };
static const char *cmd_wallpaper[]  = { "nitrogen", NULL };
static const char *cmd_shot_desktop[]  = { "sh", "-c", "scrot desktop.png && display -resize -50% desktop.png", NULL };
static const char *cmd_shot_window[]  = { "sh", "-c", "scrot -u window.png && display -resize -50% window.png", NULL };
static const char *cmd_browser[]  = { "firefox", NULL };
static const char *cmd_lock[]  = { "slock", NULL };

static Key keys[] = {
	/* modifier                     key        function     	argument */
	{ MODKEY,                       XK_p,      spawn,       	{.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,       	{.v = cmd_term } },
	{ MODKEY|ShiftMask|ControlMask, XK_Return, spawn,       	{.v = cmd_term2 } },
	{ MODKEY|ControlMask,           XK_Return, spawn,     		{.v = cmd_term3 } },
	{ MODKEY|ControlMask,           XK_f, 	   spawn,		{.v = cmd_filemgr } },
	{ MODKEY|ControlMask,           XK_n, 	   spawn,		{.v = cmd_wallpaper } },
	{ MODKEY|ControlMask,           XK_w, 	   spawn,		{.v = cmd_browser } },
	{ MODKEY,		        XK_Print,  spawn,		{.v = cmd_shot_desktop } },
	{ MODKEY|ShiftMask,	 	XK_Print,  spawn,		{.v = cmd_shot_window } },
	{ MODKEY|ControlMask, 		XK_l,      spawn,       	{.v = cmd_lock } },
	{ MODKEY,                       XK_b,      togglebar,   	{0} },
	{ MODKEY,                       XK_j,      focusstack,  	{.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,		{.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,    	{.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,    	{.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,        	{0} },
	{ MODKEY,                       XK_Tab,    view,        	{0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,  	{0} },
	{ MODKEY,                       XK_t,      setlayout,   	{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,   	{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      	{0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, 	{0} },
	{ MODKEY,                       XK_0,      view,           	{.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_Left,   view_prev_tag,  	{0} },
	{ MODKEY|ControlMask,           XK_Right,  view_next_tag,  	{0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            	{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       	{.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         	{.i = +1 } },
	TAGKEYS(                        XK_1,                      	0)
	TAGKEYS(                        XK_2,                      	1)
	TAGKEYS(                        XK_3,                      	2)
	TAGKEYS(                        XK_4,                      	3)
	TAGKEYS(                        XK_5,                      	4)
	TAGKEYS(                        XK_6,                      	5)
	TAGKEYS(                        XK_7,                      	6)
	TAGKEYS(                        XK_8,                      	7)
	TAGKEYS(                        XK_9,                      	8)
	{ MODKEY|ShiftMask,             XK_q,		quit,			{0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = cmd_term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

