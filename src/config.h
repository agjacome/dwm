#include "gaplessgrid.c"
#include "push.c"

static const char *fonts[] = {
    "xft:DroidSansMono Nerd Font:pixelsize=12:antialias=true:autohint=true",
    "xft:JoyPixels:pixelsize=12:antialias=true:autohint=true"
};

static const char dmenufont[] = "xft:DroidSansMono Nerd Font:pixelsize=12:antialias=true:autohint=true";

static const char *colors[][3] = {
    /*               fg         bg         border    */
    [SchemeNorm] = { "#5b626c", "#1d1f21", "#282a2e" }, 
    [SchemeSel]  = { "#c5c8c6", "#1d1f21", "#f0c674" }
};

static const unsigned int borderpx  = 2;
static const unsigned int snap      = 8;
static const int focusonwheel       = 0;
static const int showbar            = 1;
static const int topbar             = 1;
static const int viewontag          = 1;

static const int horizpadbar = 2;
static const int vertpadbar  = 0;

// static const char *tags[] = { "\uE000", "\uE001", "\uE008", "\uE002", "\uE006", "\uE007" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
    /* class                        instance    title           tagmask     isfloating  monitor */
    { "feh",                        NULL,       NULL,           0,          True,       0 },
    { "Pale moon",                  NULL,       NULL,           1,          False,      0 },
    { "mpv",                        NULL,       NULL,           4,          True,       0 },
    { "Spotify",                    NULL,       NULL,           4,          False,      0 },
    { "Pcmanfm",                    NULL,       NULL,           8,          False,      0 },
    { NULL,                         NULL,       "LibreOffice",  32,         False,      0 },
    { "libreoffice-calc",           NULL,       NULL,           32,         False,      0 },
    { "libreoffice-impress",        NULL,       NULL,           32,         False,      0 },
    { "libreoffice-startcenter",    NULL,       NULL,           32,         False,      0 },
    { "libreoffice-writer",         NULL,       NULL,           32,         False,      0 },
    { "Zathura",                    NULL,       NULL,           32,         False,      0 },
    { "Gimp",                       NULL,       NULL,           32,         False,      0 }
};

static const float mfact       = 0.50;
static const int   nmaster     = 1;
static const int   resizehints = 0;

static const Layout layouts[] = {
    /* symbol                 arrange function */
    // { "\uE019 \uE009 \uE019", tile        },
    // { "\uE019 \uE00C \uE019", bstack      },
    // { "\uE019 \uE00D \uE019", gaplessgrid },
    // { "\uE019 \uE00B \uE019", monocle     },
    // { "\uE019 \uE00A \uE019", NULL        },
    { "T", tile        },
    { "B", bstack      },
    { "G", gaplessgrid },
    { "M", monocle     },
    { "F", NULL        },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } }

static char        dmenumon[2] = "0"; 
static const char *dmenucmd[ ] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#1d1f21", "-nf", "#c5c8c6", "-sb", "#f0c674", "-sf", "#1d1f21", NULL };

static const char *termcmd[] = { "urxvtc", NULL };
static const char *navgcmd[] = { "palemoon", NULL };
static const char *filecmd[] = { "pcmanfm", NULL };
static const char *mailcmd[] = { "urxvtc", "-e", "mutt", NULL };
static const char *shotcmd[] = { "scrot", "-mq10", NULL };
static const char *lockcmd[] = { "slock", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "urxvtc", "-name", scratchpadname, "-geometry", "100x25", NULL };

static Key keys[] = {
    // modifier             key                 function            argument
    { MODKEY,               XK_space,           spawn,              {.v = dmenucmd      } },
    { MODKEY,               XK_Return,          spawn,              {.v = termcmd       } },
    { MODKEY,               XK_s,               togglescratch,      {.v = scratchpadcmd } },
    { MODKEY,               XK_w,               spawn,              {.v = navgcmd       } },
    { MODKEY,               XK_e,               spawn,              {.v = mailcmd       } },
    { MODKEY|ShiftMask,     XK_l,               spawn,              {.v = lockcmd       } },
    { MODKEY,               XK_d,               spawn,              {.v = filecmd       } },
    { 0,                    0xff61,             spawn,              {.v = shotcmd       } },
    { MODKEY,               XK_m,               togglebar,          {0} },
    { MODKEY,               XK_j,               focusstack,         {.i = +1 } },
    { MODKEY,               XK_k,               focusstack,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_j,               pushdown,           {.i = +1 } },
    { MODKEY|ShiftMask,     XK_k,               pushup,             {.i = -1 } },
    { MODKEY,               XK_i,               incnmaster,         {.i = +1 } },
    { MODKEY,               XK_o,               incnmaster,         {.i = -1 } },
    { MODKEY,               XK_h,               setmfact,           {.f = -0.05} },
    { MODKEY,               XK_l,               setmfact,           {.f = +0.05} },
    { MODKEY|ShiftMask,     XK_Return,          zoom,               {0} },
    { MODKEY,               XK_Tab,             view,               {0} },
    { MODKEY,               XK_q,               killclient,         {0} },
    { MODKEY,               XK_1,               setlayout,          {.v = &layouts[0]} },
    { MODKEY,               XK_2,               setlayout,          {.v = &layouts[1]} },
    { MODKEY,               XK_3,               setlayout,          {.v = &layouts[2]} },
    { MODKEY,               XK_4,               setlayout,          {.v = &layouts[3]} },
    { MODKEY,               XK_5,               setlayout,          {.v = &layouts[4]} },
    { MODKEY,               XK_0,               setlayout,          {0} },
    { MODKEY|ShiftMask,     XK_f,               togglefloating,     {0} },
    { MODKEY,               XK_p,               view,               {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_p,               tag,                {.ui = ~0 } },
    { MODKEY,               XK_comma,           focusmon,           {.i = -1 } },
    { MODKEY,               XK_period,          focusmon,           {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,           tagmon,             {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,          tagmon,             {.i = +1 } },
    { MODKEY|ShiftMask,     XK_q,               quit,               {0} },
    TAGKEYS(                XK_z,               0)
    TAGKEYS(                XK_x,               1)
    TAGKEYS(                XK_c,               2)
    TAGKEYS(                XK_v,               3)
    TAGKEYS(                XK_b,               4)
    TAGKEYS(                XK_n,               5)
};

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    // click            event mask  button      function        argument
    { ClkLtSymbol,      0,          Button1,    setlayout,      {0} },
    { ClkLtSymbol,      0,          Button3,    setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,      0,          Button2,    zoom,           {0} },
    { ClkStatusText,    0,          Button2,    spawn,          {.v = termcmd } },
    { ClkClientWin,     MODKEY,     Button1,    movemouse,      {0} },
    { ClkClientWin,     MODKEY,     Button2,    togglefloating, {0} },
    { ClkClientWin,     MODKEY,     Button3,    resizemouse,    {0} },
    { ClkTagBar,        0,          Button1,    view,           {0} },
    { ClkTagBar,        0,          Button3,    toggleview,     {0} },
    { ClkTagBar,        MODKEY,     Button1,    tag,            {0} },
    { ClkTagBar,        MODKEY,     Button3,    toggletag,      {0} },
};
