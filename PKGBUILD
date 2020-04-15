# Maintainer: Alberto G. Jácome (agjacome) <agjacome@gmail.com>
pkgname=dwm-agjacome
pkgver=r1701.e477219
pkgrel=1
pkgdesc="Heavily-patched customized build of dwm to suit my own needs"
arch=(x86_64 i686)
url="https://github.com/agjacome/dwm"
license=('MIT')
groups=()
depends=(libx11 libxinerama libxft freetype2 dmenu)
makedepends=()
checkdepends=()
optdepends=()
provides=(dwm)
conflicts=(dwm)
replaces=()
backup=()
options=()
source=("git+$url.git")
noextract=()
md5sums=('SKIP')
validpgpkeys=()

pkgver() {
    cd "$srcdir/${pkgname%-agjacome}"
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
    cd "$srcdir/${pkgname%-agjacome}"
    make
}

package() {
   cd "$srcdir/${pkgname%-agjacome}"

   make DESTDIR="${pkgdir}/" install
   install -Dm644 doc/LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
   install -Dm644 src/dwm.desktop "${pkgdir}/usr/share/xsessions/dwm.desktop"
}
