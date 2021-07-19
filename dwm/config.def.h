/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#define TERMINAL "kitty"
/* #define TERMCLASS "Kitty" */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Cascadia Code:size=10", "Mononoki Nerd Font:size=10" };
/* static const char dmenufont[]       = "monospace:size=10"; */
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#92E5CF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_cyan,  col_gray4,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "爵", "", "", "華", "", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance          title      tags mask        iscentered   isfloating   monitor */
  { "Gimp",           NULL,             NULL,       0,              0,           1,           -1 },
  { "Brave-browser",  NULL,             NULL,       1 << 0,         0,           0,           -1 },
  { "Zathura",        NULL,             NULL,       1 << 1,         0,           0,           -1 },
  { "kitty",          NULL,             NULL,       1 << 2,         0,           0,           -1 },
  { "Emacs",          NULL,             NULL,       1 << 3,         0,           0,           -1 },
  { "Rust",           NULL,             NULL,       0,              1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|M|",      centeredmaster },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ ">M>",      centeredfloatingmaster },
	{ "[D]",      deck },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *brave[]        = { "brave", "--profile-directory", NULL };
static const char *dmenucmd[]       = { "dmenu_run", NULL };
static const char *termcmd[]        = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key           function        argument */
    /* program/script spawners */
    { MODKEY,                       XK_d,         spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_BackSpace, spawn,          SHCMD("powermenu") },
    { MODKEY,                       XK_F2,        spawn,          SHCMD("brave jamboard.google.com") },
    { MODKEY,                       XK_Home,      spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause") },
    { MODKEY,                       XK_Page_Down, spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next") },
    { MODKEY,                       XK_Page_Up,   spawn,          SHCMD("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous") },
    { MODKEY,                       XK_w,         spawn,          {.v = brave } },
    { MODKEY,                       XK_Return,    spawn,          {.v = termcmd } },
    { MODKEY,                       XK_s,         spawn,          SHCMD("spotify") },
    { MODKEY,                       XK_r,         spawn,          SHCMD("kitty -e lf") },
    { MODKEY,                       XK_y,         spawn,          SHCMD("zathura /home/tarun/dl/school/11/time_table.pdf") },
    { MODKEY,                       XK_n,         spawn,          SHCMD(TERMINAL " -e nvim") },
    { MODKEY,                       XK_b,         togglebar,      {0} },
    { MODKEY,                       XK_e,         spawn,          SHCMD("emacs") },
    { MODKEY,                       XK_x,         spawn,          SHCMD("notify-send \"$(xprop | grep WM_CLASS)\"") },
    { MODKEY|ShiftMask,             XK_p,         spawn,          SHCMD("passmenu2") },
    { MODKEY|ShiftMask,             XK_a,         spawn,          SHCMD("add-bm-dir") },
    { MODKEY|ShiftMask,             XK_m,         spawn,          SHCMD("medicine-alarm") },
    /* Layouts */
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,         setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_c,         setlayout,      {.v = &layouts[5]} },
    { MODKEY|ShiftMask,             XK_l,         spawn,          SHCMD("listlayouts") },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_space,     zoom,            {0} },
	{ MODKEY|ShiftMask,             XK_f,         togglefloating,  {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,     setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,     setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,     setgaps,        {.i = 0  } },
    /* bunch of XF86 keys cos i got a bunch of em */
	{ 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer --allow-boost -d 5; kill -36 $(pidof dwmblocks);") },
	{ 0,                            XF86XK_AudioMute, spawn, SHCMD("pamixer -t; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer --allow-boost -i 5; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 5") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 5") },
	{ 0,                            XK_Print, spawn, SHCMD("flameshot gui") },
    /* struggling to make the stuff below into a function that appends to the list but
     * i am bad at C */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        MODKEY,         Button1,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
