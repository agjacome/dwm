#include "gaplessgrid.c"
#include "push.c"

static const char *fonts[] = { "DroidSansMono Nerd Font:size=10:antialias=true:autohint=true" };

static const char *colors[][3] = {
    /*               fg         bg         border    */
    [SchemeNorm] = { "#c5c8c6", "#1d1f21", "#282a2e" },
    [SchemeSel]  = { "#1d1f21", "#f0c674", "#f0c674" }
};

static const unsigned int borderpx  = 2;
static const unsigned int gappx     = 4;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const int topbar             = 1;
static const int viewontag          = 1;
static const int focusonwheel       = 0;

static const int horizpadbar = 4;
static const int vertpadbar  = 4;

static const char *tags[] = { "\uF0AC", "\uF075", "\uF03D", "\uF120", "\uF013", "\uF135" };

static const Rule rules[] = {
    /* class       instance    title    tagmask    isfloating  monitor */
    { "feh",       NULL,       NULL,    0,         1,          0 },
    { "mpv",       NULL,       NULL,    0,         1,          0 },
    { "Pale moon", NULL,       NULL,    1,         0,          0 },
};

static const float mfact       = 0.50;
static const int   nmaster     = 1;
static const int   resizehints = 0;

static const Layout layouts[] = {
    /* symbol arrange function */
    { "[]=",  tile        },
    { "TTT",  bstack      },
    { "HHH",  gaplessgrid },
    { "[M]",  monocle     },
    { "><>",  NULL        },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } }

static char        dmenumon[2] = "0";
static const char  dmenufnt[ ] = "DroidSansMono Nerd Font:size=12:antialias=true:autohint=true";
static const char *dmenucmd[ ] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufnt, "-nb", "#1d1f21", "-nf", "#c5c8c6", "-sb", "#f0c674", "-sf", "#1d1f21", "-p", "Run:", NULL };

static const char *termcmd[] = { "urxvtc", NULL };
static const char *navgcmd[] = { "palemoon", NULL };
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
