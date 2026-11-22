// Aide-memoire STI2D pour NumWorks (.nwa)
// Haut/Bas : naviguer ou defiler | OK : ouvrir | Retour : menu
#include "eadk.h"
#include <stdint.h>
#include <stdbool.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "STI2D";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

#define WHITE ((eadk_color_t)0xFFFF)
#define BLACK ((eadk_color_t)0x0000)
#define BLUE  ((eadk_color_t)0x041F)
#define LIGHT ((eadk_color_t)0xC71F)
#define GREY  ((eadk_color_t)0x7BEF)

#define SCREEN_W 320
#define SCREEN_H 240
#define HEADER_H 22
#define LINE_H 14
#define VISIBLE ((SCREEN_H - HEADER_H - 4) / LINE_H)

typedef struct { const char *title; const char *text; } Page;

static const Page pages[] = {
{ "1. Unites et conversions",
  "Base SI : m, kg, s, A, K\n"
  "Force N = kg.m/s2\n"
  "Energie J = N.m = W.s\n"
  "Puissance W = J/s\n"
  "Pression Pa = N/m2 (1 bar = 1e5 Pa)\n"
  "Couple N.m | Freq. Hz = 1/s\n"
  "Tension V | Res. Ohm | Capa F\n"
  "Prefixes: k=1e3 M=1e6 G=1e9\n"
  "          m=1e-3 u=1e-6 n=1e-9\n"
  "w (rad/s) = N (tr/min) x pi/30\n"
  "km/h -> m/s : diviser par 3,6\n"
  "1 kWh = 3,6 MJ\n"
  "1 cal = 4,18 J | 1 ch = 736 W\n"
  "T(K) = T(C) + 273,15\n"
  "1 L = 1 dm3 = 1e-3 m3\n" },

{ "2. Mecanique",
  "STATIQUE (PFS, solide a l'equilibre)\n"
  " Somme F ext = 0\n"
  " Somme M(A) ext = 0\n"
  "Moment : M = F x d (bras de levier)\n"
  "Poids : P = m x g (g = 9,81 m/s2)\n"
  "Solide a 2 forces : meme droite,\n"
  " meme norme, sens opposes\n"
  "Solide a 3 forces : concourantes,\n"
  " dynamique ferme (stat. graphique)\n"
  "Frottement : T <= f x N ; tan(phi)=f\n"
  "CINEMATIQUE\n"
  " v = omega x R | an = omega2 x R\n"
  " MRUA : v=a.t  x=a.t2/2  v2=2.a.x\n"
  " Cercle : L=2.pi.R  S=pi.R2\n"
  "TRANSMISSION\n"
  " r = Zs/Ze = Ns/Ne = ws/we\n"
  " Module m = d/Z\n"
  " Entraxe a = m.(Z1+Z2)/2\n"
  " Vis-ecrou : v = pas x tr/s\n"
  "DYNAMIQUE\n"
  " Somme F = m.a | Somme C = J.alpha\n"
  " Ec = 1/2 m v2 | Ep = m g h\n"
  " Ec rot = 1/2 J w2\n"
  " Travail W = F.d.cos(a)\n" },

{ "3. Energie et thermique",
  "Puissance meca : P = F.v | P = C.w\n"
  "Energie : E = P x t\n"
  "Rendement : eta = Ps/Pe  (< 1)\n"
  "Chaine : eta = eta1 x eta2 x ...\n"
  "Pertes = Pe - Ps\n"
  "THERMIQUE\n"
  " Q = m.c.dT | c eau = 4180 J/kg.K\n"
  " P = Q/t\n"
  " Conduction : phi = lambda.S.dT/e\n"
  " Rth = e/(lambda.S) | phi = dT/Rth\n"
  "RENOUVELABLES\n"
  " Eolien : P = 1/2.rho.S.v3.Cp\n"
  "  rho air = 1,2 | Betz Cp < 59 %\n"
  " Photovoltaique : P = S.E.eta\n"
  "  (E = 1000 W/m2 en STC)\n"
  " Hydraulique : P = rho.g.Q.H.eta\n"
  " Pneumatique/hydr. : F = p x S\n"
  "Batterie : E(Wh) = U x C(Ah)\n"
  "Autonomie = capacite / courant\n" },

{ "4. Electricite",
  "Ohm : U = R.I | P = R.I2 = U2/R\n"
  "Serie : Req = R1 + R2\n"
  "Parallele : 1/Req = 1/R1 + 1/R2\n"
  "Diviseur : Us = Ue.R2/(R1+R2)\n"
  "Noeuds : somme I = 0\n"
  "Mailles : somme U = 0\n"
  "Condensateur : Q=C.U | i=C.du/dt\n"
  "RC : tau=R.C | 63 % a tau, 99 % a 5tau\n"
  "RL : tau = L/R | u = L.di/dt\n"
  "ALTERNATIF\n"
  " Ueff = Umax/sqrt2 | T = 1/f\n"
  " w = 2.pi.f | secteur 230 V 50 Hz\n"
  " P = U.I.cos(phi)    (W)\n"
  " Q = U.I.sin(phi)    (var)\n"
  " S = U.I             (VA)\n"
  " S2 = P2 + Q2 | fp = cos(phi)\n"
  "TRIPHASE (230/400 V)\n"
  " P = sqrt3.U.I.cos(phi)\n"
  " Etoile : U = sqrt3.V ; I = J\n"
  " Triangle : U = V ; I = sqrt3.J\n"
  "Transfo : m = U2/U1 = N2/N1\n"
  "Moteur CC : U = E + R.I ; C = k.I\n"
  "Asynchrone : ns = 60.f/p\n"
  "  glissement g = (ns - n)/ns\n"
  "LED : R = (Valim - Vled)/I\n"
  "Diode : seuil ~ 0,6 a 0,7 V\n" },

{ "5. Resistance des mat.",
  "Traction : sigma = F/S (MPa=N/mm2)\n"
  "Deformation : eps = dL/L0\n"
  "Hooke : sigma = E.eps\n"
  " E acier ~ 210 GPa | alu ~ 70 GPa\n"
  "Condition : sigma <= Re/s\n"
  " (s = coefficient de securite)\n"
  "Cisaillement : tau = T/S\n"
  " condition : tau <= Rg/s\n"
  "Torsion : tau = Mt.r/I0\n"
  " I0 cercle = pi.d4/32\n"
  "Flexion : sigma = Mf.v/Igz\n"
  " rectangle : Igz = b.h3/12\n"
  " cercle : Igz = pi.d4/64\n"
  "Section : cercle pi.d2/4\n"
  "Masse volumique : rho = m/V\n"
  " acier 7800 | alu 2700 kg/m3\n" },

{ "6. Numerique et info",
  "2^8=256 | 2^10=1024 | 2^12=4096\n"
  "2^16=65536\n"
  "n bits -> 2^n valeurs\n"
  "Hexa : A=10 B=11 C=12 D=13 E=14 F=15\n"
  "1 octet = 8 bits\n"
  "CAN : q = Vref/2^n | N = Vin/q\n"
  "Shannon : fe >= 2.fmax\n"
  "Debit : t = taille / debit\n"
  "LOGIQUE\n"
  " ET = a.b | OU = a+b | NON = /a\n"
  " XOR : 1 si entrees differentes\n"
  " De Morgan : /(a.b) = /a + /b\n"
  "                /(a+b) = /a . /b\n"
  "Capteur : TOR / analog. / numerique\n" },

{ "7. Systemes (SII)",
  "CHAINE D'INFORMATION\n"
  " Acquerir - Traiter - Communiquer\n"
  "CHAINE D'ENERGIE\n"
  " Alimenter - Distribuer - Convertir\n"
  " - Transmettre\n"
  "Preactionneur -> actionneur\n"
  "SYSML\n"
  " req : exigences | uc : cas d'util.\n"
  " bdd : blocs | ibd : blocs internes\n"
  " seq : sequence | stm : etats\n"
  " act : activite\n"
  "ASSERVISSEMENT\n"
  " Ecart = consigne - mesure\n"
  " Criteres : precision, rapidite,\n"
  "  stabilite\n"
  " 1er ordre : K/(1+tau.p)\n"
  "  63 % a tau | 95 % a 3.tau\n"
  "BO : pas de retour | BF : retour\n" },

{ "8. Dev. durable",
  "ACV : extraction, fabrication,\n"
  " transport, usage, fin de vie\n"
  "Eco-conception : reduire l'impact\n"
  " a chaque etape du cycle de vie\n"
  "3R : Reduire, Reutiliser, Recycler\n"
  "Energie primaire -> finale -> utile\n"
  "Renouvelable : solaire, eolien,\n"
  " hydraulique, biomasse, geothermie\n"
  "Non renouvelable : fossile, nucleaire\n"
  "Indicateurs : empreinte carbone,\n"
  " consommation, recyclabilite\n" },

{ "9. Maths utiles",
  "Pythagore : a2 = b2 + c2\n"
  "Trigo : sin = opp/hyp\n"
  "        cos = adj/hyp\n"
  "        tan = opp/adj\n"
  "sin2 + cos2 = 1\n"
  "Aire : disque pi.R2 | tri. b.h/2\n"
  "Volume : cylindre pi.R2.h\n"
  "         sphere 4/3.pi.R3\n"
  "Derivees : (x^n)' = n.x^(n-1)\n"
  " (sin)'=cos | (cos)'=-sin\n"
  " (e^x)'=e^x | (ln x)'=1/x\n"
  "Pourcentage : x.(1 + t/100)\n"
  "Log : log(a.b)=log a+log b\n"
  "Decibel : G(dB) = 20.log(Us/Ue)\n"
  "Degres -> rad : x pi/180\n" }
};

#define NPAGES ((int)(sizeof(pages) / sizeof(pages[0])))

static void fill(int x, int y, int w, int h, eadk_color_t c) {
  eadk_display_push_rect_uniform((eadk_rect_t){x, y, w, h}, c);
}

static void header(const char *title) {
  fill(0, 0, SCREEN_W, HEADER_H, BLUE);
  eadk_display_draw_string(title, (eadk_point_t){4, 3}, false, WHITE, BLUE);
}

static int count_lines(const char *t) {
  int n = 0;
  while (*t) { if (*t == '\n') n++; t++; }
  return n;
}

static void draw_menu(int sel) {
  fill(0, 0, SCREEN_W, SCREEN_H, WHITE);
  header("STI2D - Aide-memoire");
  for (int i = 0; i < NPAGES; i++) {
    int y = HEADER_H + 6 + i * 22;
    eadk_color_t bg = (i == sel) ? LIGHT : WHITE;
    fill(0, y - 2, SCREEN_W, 22, bg);
    eadk_display_draw_string(pages[i].title, (eadk_point_t){8, y}, true, BLACK, bg);
  }
}

static void draw_page(const Page *p, int scroll) {
  fill(0, 0, SCREEN_W, SCREEN_H, WHITE);
  header(p->title);
  const char *s = p->text;
  int i = 0;
  while (*s) {
    char buf[48];
    int n = 0;
    while (*s && *s != '\n') { if (n < 46) buf[n++] = *s; s++; }
    buf[n] = 0;
    if (*s == '\n') s++;
    if (i >= scroll && i < scroll + VISIBLE) {
      eadk_display_draw_string(buf, (eadk_point_t){4, HEADER_H + 2 + (i - scroll) * LINE_H},
                               false, BLACK, WHITE);
    }
    i++;
  }
  int total = count_lines(p->text);
  if (scroll > 0)
    eadk_display_draw_string("^", (eadk_point_t){308, HEADER_H + 2}, false, GREY, WHITE);
  if (scroll + VISIBLE < total)
    eadk_display_draw_string("v", (eadk_point_t){308, SCREEN_H - 16}, false, GREY, WHITE);
}

int main(int argc, char *argv[]) {
  int sel = 0, scroll = 0;
  bool in_page = false;
  draw_menu(sel);

  while (true) {
    eadk_keyboard_state_t k = eadk_keyboard_scan();
    bool redraw = false;

    if (!in_page) {
      if (eadk_keyboard_key_down(k, eadk_key_down) && sel < NPAGES - 1) { sel++; redraw = true; }
      else if (eadk_keyboard_key_down(k, eadk_key_up) && sel > 0)       { sel--; redraw = true; }
      else if (eadk_keyboard_key_down(k, eadk_key_ok)) {
        in_page = true; scroll = 0;
        draw_page(&pages[sel], scroll);
        eadk_timing_msleep(250);
        continue;
      }
      if (redraw) { draw_menu(sel); eadk_timing_msleep(130); }
    } else {
      int total = count_lines(pages[sel].text);
      int maxs = total > VISIBLE ? total - VISIBLE : 0;
      if (eadk_keyboard_key_down(k, eadk_key_down) && scroll < maxs) { scroll++; redraw = true; }
      else if (eadk_keyboard_key_down(k, eadk_key_up) && scroll > 0)  { scroll--; redraw = true; }
      else if (eadk_keyboard_key_down(k, eadk_key_back)) {
        in_page = false;
        draw_menu(sel);
        eadk_timing_msleep(250);
        continue;
      }
      if (redraw) { draw_page(&pages[sel], scroll); eadk_timing_msleep(90); }
    }
    eadk_timing_msleep(20);
  }
  return 0;
}
