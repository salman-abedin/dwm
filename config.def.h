/*  ____   __        __  __  __      ____                    __   _ */
/* |  _ \  \ \      / / |  \/  |    / ___|   ___    _ __    / _| (_)   __ _ */
/* | | | |  \ \ /\ / /  | |\/| |   | |      / _ \  | '_ \  | |_  | |  / _` | */
/* | |_| |   \ V  V /   | |  | |   | |___  | (_) | | | | | |  _| | | | (_| | */
/* |____/     \_/\_/    |_|  |_|    \____|  \___/  |_| |_| |_|   |_|  \__, | */
/*                                                                    |___/ */

/* /1* See LICENSE file for copyright and license details. *1/ */

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int gappx = 15;   /* gap pixel between windows */

static const unsigned int snap = 32; /* snap pixel */

static const int showbar = 1;  /* 0 means no bar */
static const int topbar = 0;   /* 0 means bottom bar */
static const int user_bh = 25; /* 0 means that dwm will calculate bar height, >=
                                 1 means dwm will user_bh as bar height */
/* static const int vertpad = 5;  /1* vertical padding of bar *1/ */
/* static const int sidepad = 360; /1* horizontal padding of bar *1/ */
static const int vertpad = 0; /* vertical padding of bar */
static const int sidepad = 0; /* horizontal padding of bar */

static const char *fonts[] = {
    "sans-serif:size=15:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=12:antialias=true:autohint=true",
};

static const char dmenufont[] = "sans-serif:size=15";

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
static const char sel_bg[] = "#222222";
static const char sel_border[] = "#0000ff";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
    [SchemeSel] = {sel_fg, sel_bg, sel_border},
};

static const char *tags[] = {
    "🕳",
    "🕳",
    "🕳",
};

static const char *alttags[] = {"", "🕸", "🎵"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Brave-browser", 0, 0, 1 << 1, 0, -1},
    {"firefox", 0, 0, 1 << 1, 0, -1},
    {"Spotify", 0, 0, 1 << 2, 0, -1},
    {"Microsoft Teams - Preview", 0, 0, 1 << 2, 0, -1},
    {"calibre", 0, 0, 1 << 2, 0, -1},
    {"presenter", 0, 0, 1 << 2, 0, -1},
    {"mpv", 0, 0, 1 << 2, 1, -1},
    {"MuseScore3", 0, 0, 1 << 2, 1, -1},
    {"st-256color", 0, 0, 1, 0, -1},
};

/* layout(s) */
static const float mfact = 0.63; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"🎸", monocle}, /* first entry is default */
    {"", tile},
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
#define TAGKEYS(KEY, TAG)                                       \
   {MODKEY, KEY, view, {.ui = 1 << TAG}},                       \
       {MODKEY | ShiftMask, KEY, toggleview, {.ui = 1 << TAG}}, \
       {MODKEY | Mod1Mask, KEY, tag, {.ui = 1 << TAG}},         \
       {MODKEY | Mod1Mask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#include <X11/XF86keysym.h>

#include "patches/actualfullscreen.c"
#include "patches/inplacerotate.c"
#include "patches/shiftviewactive.c"
static Key keys[] = {
    /* modifier                     key        function        argument */

    //--------------------------------------
    //              WM stuff
    //--------------------------------------

    {MODKEY, XK_h, inplacerotate, {.i = -2}},
    {MODKEY, XK_k, shiftviewactive, {.i = +1}},
    {MODKEY, XK_j, shiftviewactive, {.i = -1}},
    {MODKEY, XK_l, inplacerotate, {.i = +2}},

    {MODKEY, XK_semicolon, killclient, {0}},
    {MODKEY, XK_m, setlayout, {0}},

    {MODKEY, XK_period, focusstack, {.i = +1}},
    {MODKEY, XK_comma, focusstack, {.i = -1}},

    /* {MODKEY | ShiftMask, XK_b, togglebar, {0}}, */
    {MODKEY, XK_p, togglebar, {0}},
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, quit, {0}},

    /* Resize */
    {MODKEY | Mod1Mask, XK_h, setmfact, {.f = -0.05}},
    {MODKEY | Mod1Mask, XK_l, setmfact, {.f = +0.05}},

    /* {MODKEY, XK_Return, zoom, {0}}, */
    /* {MODKEY, XK_m, setlayout, {.v = &layouts[2]}}, */
    /* {MODKEY | ShiftMask, XK_space, togglefloating, {0}}, */

    /* /1* Bring to master *1/ */
    /* {MODKEY, XK_i, zoom, {0}}, */

    //--------------------------------------
    //              Commands
    //--------------------------------------

    {MODKEY, XK_Return, spawn, SHCMD("launch -T")},

    {MODKEY, XK_b, spawn, SHCMD("$BROWSER")},
    {MODKEY, XK_e, spawn, SHCMD("insertemoji")},
    {MODKEY, XK_f, spawn, SHCMD("toggle -f")},
    /* {MODKEY, XK_h, spawn, SHCMD("xrandr -o left")}, */
    /* {MODKEY | ShiftMask, XK_h, spawn, */
    /*  SHCMD("xrandr -o normal && xrandr -s 1366x768")}, */
    {MODKEY, XK_o, spawn, SHCMD("launch --bolt")},
    /* {MODKEY, XK_o, spawn, SHCMD("bolt --tmux-search")}, */
    /* {MODKEY, XK_p, spawn, SHCMD("xdotool keyup p key --clearmodifiers Control+Shift+v")}, */
    /* {MODKEY, XK_a, spawn, SHCMD("xdotool key Caps_Lock")}, */
    {MODKEY, XK_r, spawn, SHCMD("dmenu_run")},
    {MODKEY, XK_s, spawn, SHCMD("toggle --screen_key")},
    {MODKEY, XK_t, spawn, SHCMD("alacritty")},
    {MODKEY, XK_u, spawn, SHCMD("unimark")},
    /* {MODKEY | ShiftMask, XK_u, spawn, SHCMD("unipass")}, */
    {MODKEY, XK_i, spawn, SHCMD("unipass add")},
    {MODKEY | ShiftMask, XK_i, spawn, SHCMD("unipass fetch")},
    {MODKEY, XK_w, spawn, SHCMD("setdisplay --bg shuffle")},

    {0, XK_F1, spawn, SHCMD("setplayer --vol toggle")},
    {0, XK_F2, spawn, SHCMD("setplayer --vol down")},
    {0, XK_F3, spawn, SHCMD("setplayer --vol up")},
    {0, XK_F11, spawn, SHCMD("backlight --down")},
    {0, XK_F12, spawn, SHCMD("backlight --up")},

    {0, XK_Print, spawn, SHCMD("record -s")},
    {MODKEY, XK_Print, spawn, SHCMD("record -d")},
    /* {0, XK_Print, spawn, SHCMD("maim -u -d 1 ~/screenshot_\"$(date */
    /*    +'%Y-%d%b-%H%M%S')\".png")}, */
    /* {0 | ShiftMask, XK_Print, spawn, SHCMD("maim -B -u -d 1 -s
       ~/screenshot_"$(date +'%Y-%d%b-%H%M%S')".png")}, */

    {0, XK_KP_Home, spawn, SHCMD("blue -c")},
    {MODKEY, XK_KP_Home, spawn, SHCMD("blue -t")},
    {0, XK_KP_Left, spawn, SHCMD("toggle --screen_text")},
    /* {0, XK_KP_Begin, spawn, SHCMD("timer")}, */

    {0, XK_KP_Subtract, spawn, SHCMD("leavex -c")},
    {MODKEY, XK_KP_Subtract, spawn, SHCMD("leavex -s")},
    {0, XK_KP_End, spawn, SHCMD("pkill -u $USER")},

    {0, XK_KP_Delete, spawn, SHCMD("lock -f")},

    /* {0, XK_KP_Delete, spawn, SHCMD("pkill -u $USER")}, */
    /* {0, XK_KP_Insert, spawn, SHCMD("sleep 1 && xset dpms force off")}, */
    {0, XK_KP_Insert, spawn, SHCMD("lock")},
    /* {0, XK_KP_Add, spawn, SHCMD("systectl suspend")}, */

    /* {MODKEY, XK_k, spawn, */
    /*  SHCMD("xdotool key Super+shift+comma && xdotool key Super+Shift+m")}, */

    {0, XF86XK_AudioPrev, spawn, SHCMD("setplayer --play prev")},
    {0, XF86XK_AudioNext, spawn, SHCMD("setplayer --play next")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("setplayer --play toggle")},

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
