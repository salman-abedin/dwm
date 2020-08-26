/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */

static const unsigned int snap = 32; /* snap pixel */

static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */

static const int vertpad = 10;  /* vertical padding of bar */
static const int sidepad = 380; /* horizontal padding of bar */

static const char *fonts[] = {
    "sans:size=15",
    "Noto Color Emoji:pixelsize=12:antialias=true:autohint=true",
};

static const char dmenufont[] = "sans:size=15";

//==============================================================================
//                             Colors
//==============================================================================

static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";

static const char norm_fg[] = "#ffffff";
static const char norm_bg[] = "#000000";
static const char norm_border[] = "#ffffff";

static const char sel_fg[] = "#ffffff";
static const char sel_bg[] = "#000000";
static const char sel_border[] = "#0000ff";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
    [SchemeSel] = {sel_fg, sel_bg, sel_border},
};

static const char *tags[] = {
    "",
    "🕸",
    "🎼",
};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    /* {"Gimp", NULL, NULL, 0, 1, -1}, */
    {"firefox", 0, 0, 2, 0, -1},
};

/* layout(s) */
static const float mfact = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"🗃 ", tile}, /* first entry is default */
    {"🎸", monocle},
    {"><>", NULL}, /* no layout function means floating behavior */
};

//==============================================================================
//                             Commands
//==============================================================================

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                         \
   {                                                       \
      .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
   }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};

//==============================================================================
//                             Keyboard Bindings
//==============================================================================

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                         \
   {MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
       {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
       {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
       {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* #include <X11/XF86keysym.h> */
#include "patches/nextprevtag.c"
static Key keys[] = {
    /* modifier                     key        function        argument */

    //--------------------------------------
    //              WM stuff
    //--------------------------------------

    {MODKEY, XK_l, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},

    /* {MODKEY, XK_j, shiftview, {.i = -1}}, */
    /* {MODKEY, XK_semicolon, shiftview, {.i = +1}}, */

    {MODKEY, XK_semicolon, view_adjacent, {.i = +1}},
    {MODKEY, XK_j, view_adjacent, {.i = -1}},

    {MODKEY, XK_n, killclient, {0}},
    {MODKEY, XK_m, setlayout, {0}},

    {MODKEY, XK_Tab, view, {0}},

    /* Resize */
    {MODKEY | Mod1Mask, XK_j, setmfact, {.f = -0.05}},
    {MODKEY | Mod1Mask, XK_semicolon, setmfact, {.f = +0.05}},

    /* {MODKEY | ShiftMask, XK_b, togglebar, {0}}, */

    /* {MODKEY, XK_Return, zoom, {0}}, */

    /* {MODKEY, XK_t, setlayout, {.v = &layouts[0]}}, */
    /* {MODKEY, XK_f, setlayout, {.v = &layouts[1]}}, */
    /* {MODKEY, XK_m, setlayout, {.v = &layouts[2]}}, */
    /* {MODKEY | ShiftMask, XK_space, togglefloating, {0}}, */

    {MODKEY, XK_q, quit, {0}},

    //--------------------------------------
    //              Commands
    //--------------------------------------

    {MODKEY, XK_Return, spawn, SHCMD("launch -T")},

    {MODKEY, XK_b, spawn, SHCMD("$BROWSER")},
    {MODKEY, XK_e, spawn, SHCMD("insertemoji")},
    {MODKEY, XK_o, spawn, SHCMD("bolt --tmux-search")},
    {MODKEY, XK_p, spawn, SHCMD("mirror --git")},
    {MODKEY, XK_r, spawn, SHCMD("dmenu_run")},
    {MODKEY, XK_t, spawn, SHCMD("alacritty")},
    {MODKEY, XK_w, spawn, SHCMD("setdisplay --bg shuffle")},

    {0, XK_F1, spawn, SHCMD("setplayer --vol toggle")},
    {0, XK_F2, spawn, SHCMD("setplayer --vol down")},
    {0, XK_F3, spawn, SHCMD("setplayer --vol up")},
    {0, XK_F11, spawn, SHCMD("backlight --down")},
    {0, XK_F12, spawn, SHCMD("backlight --up")},

    {0, XK_Print, spawn, SHCMD("screencast")},

    {0, XK_KP_Home, spawn, SHCMD("connectbt")},
    {0, XK_KP_End, spawn, SHCMD("pkill -u $USER")},
    {0, XK_KP_Left, spawn, SHCMD("timer")},
    {0, XK_KP_Delete, spawn, SHCMD("pkill -u $USER")},
    {0, XK_KP_Insert, spawn, SHCMD("sleep 1 && xset dpms force off")},
    {0, XK_KP_Add, spawn, SHCMD("systectl suspend")},

    //--------------------------------------
    //              Tags
    //--------------------------------------

    /* {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}}, // Sticky */
    {MODKEY, XK_0, view, {.ui = ~0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

//==============================================================================
//                             Mouse Bindings
//==============================================================================

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
