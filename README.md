My own customized build of dwm
==============================

![Screenshot](doc/screenshot.png)

**[dwm](https://dwm.suckless.org/)** is an extremely fast tiling window manager
for X. This is my personal build of dwm. The current build includes the
following patches:

* [attachaside](https://dwm.suckless.org/patches/attachaside/): make new
  clients appear in the stacking area instead of master
* [bottomstack](https://dwm.suckless.org/patches/bottomstack/): layout which
  puts the stacking area at the bottom
* [focusonclick](https://dwm.suckless.org/patches/focusonclick/): make clients
  focused only by mouse click and not only by mouse hover
* [gaplessgrid](https://dwm.suckless.org/patches/gaplessgrid/): layout which
  arranges all clients in a grid
* [noborder](https://dwm.suckless.org/patches/noborder/): remove border when
  there is only one client visible
* [push](https://dwm.suckless.org/patches/push/): move clients through the
  list with simple keybinds
* [scratchpad](https://dwm.suckless.org/patches/scratchpad/): spawn or restore
  a single floating terminal client
* [statuspadding](https://dwm.suckless.org/patches/statuspadding/): make
  horizontal and vertical padding of the statusbar configurable
* [uselessgap](https://dwm.suckless.org/patches/uselessgap/): add a
  configurable gap around clients for aesthetics purposes
* [viewontag](https://dwm.suckless.org/patches/viewontag/): follow clients to
  the tag they are being moved to

### Installing on ArchLinux

All you need to do is download the `PKGBUILD` file from this repository and
build the ArchLinux package with `makepkg`:

```
curl -Ls https://raw.githubusercontent.com/agjacome/dwm/master/PKGBUILD > PKGBUILD
makepkg -scf
```

This will generate a package file that you will be able to install with
`pacman`:

```
sudo pacman -U dwm-agjacome*.pkg.tar.xz
```
