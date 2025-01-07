`timescale 1ns / 1ps

module square(
        input a,
        input b,
        input c,
        output[5:0] value
    );
    wire na, nb, nc;
    wire x, nw, w, anbc, nabc, anb, ac, nv, v, u;
    not notA(na, a);
    not notB(nb, b);
    not notC(nc, c);
    nor nor1(x, nb, c);
    nor nor2(anbc, na, b, nc);
    nor nor3(nabc, a, nb, nc);
    nor nor4(nw, anbc, nabc); 
    not notNW(w, nw);
    nor nor5(anb, na, b);
    nor nor6(ac, na, nc);
    nor nor7(nv, anb, ac);
    not notNV(v, nv);
    nor nor8(u, na, nb);
    assign value[0] = c;
    assign value[1] = 0;
    assign value[2] = x;
    assign value[3] = w;
    assign value[4] = v;
    assign value[5] = u;
endmodule