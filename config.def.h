#include <stdlib.h>
#include <stdbool.h>
#include <X11/XF86keysym.h>


static const unsigned int borderpx = 2;
static const unsigned int gappx = 12;
static const unsigned int snap = 0;
static const int showbar = true;
static const int topbar = true;
static const char *fonts[] = { "Iosevka Nerd Font Mono:size=13", "monospace:size=13" }; // main and fallback font

// colorscheme
#define col_gray1 "#222222"
#define col_gray2 "#444444"
#define col_gray3 "#bbbbbb"
#define col_gray4 "#eeeeee"
#define col_cyan "#344e5b"
#define col_green "#6ac769"
#define col_yellow "#e5c63f"
#define col_white "#f8ecaa"
#define col_red "#e3433f"

#define col_1 "#cf8592"
#define col_2 "#165a5d"
#define col_3 "#eab8bb"
#define col_4 "#298657"

static const char *colors[][3] = {
//                   primary    secondary    border
	[SchemeNorm] = { col_3, col_2, col_4 },
	[SchemeSel]  = { col_2, col_1,  col_1},
};

//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{"Gimp", NULL, NULL, 0, 1, -1},
	{"CoreShot", NULL, NULL, 0, 1, -1},
	{"Media Viewer", NULL, NULL, 0, 1, -1},
};
// factor of master area size
static const float mfact = 0.5; 
// number of clients in master area
static const int nmaster = 1;
//1 means respect size hints in tiled resizals
static const int resizehints = false;
//1 will force focus on the fullscreen window
static const int lockfullscreen = true;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "master-stack", tile },
	{ "centered-master-float", centeredfloatingmaster },
	{ "centered-master", centeredmaster },
	{ "float", NULL },
	{ "monocle", monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define TERMINAL "alacritty"

/* commands */
static const char *dmenucmd[] = {"dmenu_run", NULL};
static const char *termcmd[] = {TERMINAL, NULL};
static const char *browsercmd[] = {"librewolf", NULL};
static const char *screenshotcmd[] = {"flameshot", "gui", NULL};
static const char *mr_crabs_cmd[] = {TERMINAL, "-e", "ssh", "mr-crabs", NULL};

static const char *volumeupcmd[] = {"pulsemixer", "--change-volume", "+5", NULL};
static const char *volumedowncmd[] = {"pulsemixer", "--change-volume", "-5", NULL};
static const char *audiotogglecmd[] = {"playerctl", "play-pause"};

static const char *brightnessupcmd[] = {"brightnessctl", "set", "+10%", NULL};
static const char *brightnessdowncmd[] = {"brightnessctl", "set", "10-%", NULL};

static const Key keys[] = {
//   modifier, key, function, argument
//   running programs
	{MODKEY, XK_space, spawn, {.v = dmenucmd}},
	{MODKEY, XK_Return, spawn, {.v = termcmd }},
	{MODKEY|ShiftMask, XK_b, spawn, {.v = browsercmd }},
	{MODKEY|ShiftMask, XK_s, spawn, {.v = screenshotcmd }},
    {MODKEY, XK_m, spawn, {.v = mr_crabs_cmd}},
// media playback
	{0, XF86XK_AudioLowerVolume, spawn, {.v = volumedowncmd}},
	{0, XF86XK_AudioRaiseVolume, spawn, {.v = volumeupcmd}},
    {0, XF86XK_AudioPlay, spawn, {.v = audiotogglecmd}},
    {0, 0x1008ff14, spawn, {.v = audiotogglecmd}},
// change the brightness
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightnessupcmd}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightnessdowncmd}},
// toggle bar visibility
	{MODKEY, XK_b, togglebar, {0}},
// change window focus
	{MODKEY, XK_l, focusstack, {.i = +1 }},
	{MODKEY, XK_k, focusstack, {.i = -1 }},
// change number of master clients
	{MODKEY, XK_s, incnmaster, {.i = +1 }},
	{MODKEY, XK_d, incnmaster, {.i = -1 }},
// change size of mastere client area
	{MODKEY, XK_j, setmfact, {.f = -0.05}},
	{MODKEY, XK_semicolon, setmfact, {.f = +0.05}},
// set window as master
	{MODKEY, XK_f, zoom, {0}},
// move floating windows
	{MODKEY|ShiftMask, XK_j, movex, {.i = -25}},
	{MODKEY|ShiftMask, XK_semicolon, movex, {.i = 25}},
	{MODKEY|ShiftMask, XK_k, movey, {.i = 25}},
	{MODKEY|ShiftMask, XK_l, movey, {.i = -25}},
// cycle between the two last used tags
	{MODKEY, XK_Tab, view, {0}},
// kill the focused client
	{MODKEY, XK_q, killclient, {0}},
// change to master-stack layout
	{MODKEY, XK_e, setlayout, {.v = &layouts[0]}},
// change to centered-floating-master layout
	{MODKEY, XK_r, setlayout, {.v = &layouts[1]}},
// change to centered-master layout
	{MODKEY, XK_t, setlayout, {.v = &layouts[2]}},
// change to floating layout
	{MODKEY, XK_y, setlayout, {.v = &layouts[3]}},
// change to monocle layout
	{MODKEY, XK_u, setlayout, {.v = &layouts[4]}},
// toggle floating status for client
	{MODKEY, XK_w, togglefloating, {0}},
// toggle fullscreen status for client
    {MODKEY|ShiftMask, XK_f, togglefullscr, {0}},
// view all tags
	{MODKEY, XK_0, view, {.ui = ~0 }},
// tag client with all tags
	{MODKEY|ShiftMask, XK_0, tag, {.ui = ~0 }},
// focus previous monitor
	{MODKEY, XK_comma, focusmon, {.i = -1 }},
// focus next monitor
	{MODKEY, XK_period, focusmon, {.i = +1 }},
// move client to previous monitor
	{MODKEY|ShiftMask, XK_comma, tagmon, {.i = -1 }},
// move client to next monitor
	{MODKEY|ShiftMask, XK_period, tagmon, {.i = +1 }},
// tagkeys
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
// restart dwm
	{MODKEY|ControlMask|ShiftMask, XK_q, quit, {0}},
// quit dwm
	{MODKEY|ControlMask|ShiftMask, XK_r, quit, {1}},
};

// button config
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
static const Button buttons[] = {
//    click                event mask      button          function        argument
	{ClkLtSymbol, 0, Button1, setlayout, {0}},
	{ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
	{ClkWinTitle, 0, Button2, zoom, {0}},
	{ClkStatusText, 0, Button2, spawn, {.v = termcmd }},
	{ClkClientWin, MODKEY, Button1, movemouse, {0}},
	{ClkClientWin, MODKEY, Button2, togglefloating, {0}},
	{ClkClientWin, MODKEY, Button3, resizemouse, {0}},
	{ClkTagBar, 0, Button1, view, {0}},
	{ClkTagBar, 0, Button3, toggleview, {0}},
	{ClkTagBar, MODKEY, Button1, tag, {0}},
	{ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
