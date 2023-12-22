#include "Menu.h"

//复杂样例A(B(E(F,G),C(H,D(I(K,L),))),)
//A(B(,C(D(G,E(,F(H(I(,J(,K(,L))),),))),)),)
//A(B(D(F(,G(I,H(J,K))),E),C),)

int main() {
    Menu menu;
    menu.Welcome();
    menu.DoMenu();
    return 0;
}
