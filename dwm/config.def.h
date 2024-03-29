/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoMedium Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMonoMedium Nerd Font:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { "alacritty", "-e", "ncspot", "-t", "ncspot", "-d", "0", "0" };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"ncspot",    spcmd1},
};

/* tagging */
static const char *tags[] = { "爵", "", "", "華", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance          title      tags mask        switchtotag     iscentered   isfloating   monitor */
  { "Gimp",           NULL,             NULL,       0,              0,              0,           1,           -1 },
  { "Brave-browser",  NULL,             NULL,       1 << 0,         1,              0,           0,           -1 },
  { "Google-chrome",  NULL,             NULL,       1 << 8,         0,              0,           0,           -1 },
  { "Zathura",        NULL,             NULL,       1 << 1,         1,              0,           0,           -1 },
  { "Alacritty",      NULL,             NULL,       1 << 2,         1,              0,           0,           -1 },
  { "Emacs",          NULL,             NULL,       1 << 3,         1,              0,           0,           -1 },
  { "Tk",             NULL,             NULL,       0,              0,              1,           1,           -1 },
  { NULL,		      "ncspot",	        NULL,		SPTAG(0),		0,			    0,           0,           -1 },
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
static const char *brave[]          = { "brave", NULL };
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]        = { "alacritty", NULL };


#include "selfrestart.c"

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
    { MODKEY,                       XK_r,         spawn,          SHCMD("alacritty -e lf") },
    { MODKEY,                       XK_y,         spawn,          SHCMD("zathura /home/tarun/dl/school/11/time_table.pdf") },
    { MODKEY,                       XK_n,         spawn,          SHCMD(TERMINAL " -e nvim") },
    { MODKEY,                       XK_b,         togglebar,      {0} },
    { MODKEY,                       XK_e,         spawn,          SHCMD("emacs") },
    { MODKEY,                       XK_x,         spawn,          SHCMD("notify-send \"$(xprop | grep WM_CLASS)\"") },
	{ MODKEY,            			XK_s,  	      togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_c,  	      spawn,          SHCMD("clipmenu") },
    { MODKEY|ShiftMask,             XK_p,         spawn,          SHCMD("passmenu2") },
    { MODKEY|ShiftMask,             XK_a,         spawn,          SHCMD("add-bm-dir") },
    { MODKEY|ShiftMask,             XK_m,         spawn,          SHCMD("medicine-alarm") },
    { MODKEY|ShiftMask,             XK_b,         spawn,          SHCMD("echo 'JetBrainsMonoMedium Nerd Font' | xclip -sel clip") },
    { MODKEY|ShiftMask,             XK_k,         spawn,          SHCMD("killmenu") },
    { MODKEY|ShiftMask,             XK_r,         spawn,          SHCMD("alacritty -e recompile-dwm") },
    /* Layouts */
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,         setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_z,         setlayout,      {.v = &layouts[5]} },
    { MODKEY|ShiftMask,             XK_l,         spawn,          SHCMD("listlayouts") },
	{ MODKEY|Mod1Mask,              XK_j,         aspectresize,   {.i = +24} },
	{ MODKEY|Mod1Mask,              XK_k,         aspectresize,   {.i = -24} },
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
	/* { Mod1Mask,                            XK_F1,        spawn,          SHCMD("pomo pause; kill -41 $(pidof dwmblocks)") }, */
	/* { Mod1Mask,                            XK_F2,        spawn,          SHCMD("pomo start; kill -41 $(pidof dwmblocks)") }, */
	/* { Mod1Mask,                            XK_F3,        spawn,          SHCMD("kill -41 $(pidof dwmblocks)") }, */
	/* { Mod1Mask,                            XK_F4,        spawn,          SHCMD("pomo stop; kill -41 $(pidof dwmblocks)") }, */
    /* bunch of XF86 keys coz i got a bunch of em */
	{ 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer --allow-boost -d 5; kill -36 $(pidof dwmblocks);") },
	{ 0,                            XF86XK_AudioMute, spawn, SHCMD("pamixer -t; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer --allow-boost -i 5; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 5") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 5") },
	{ 0,                            XK_Print, spawn, SHCMD("flameshot gui") },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
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
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
