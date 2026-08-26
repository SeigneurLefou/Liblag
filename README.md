# ALG (AsciiLibGraphic)

## Function Todo

### Constructor and destructor

* `bool alg_init()` — Initialise le contexte principal de ncurses (`initscr`, `cbreak`, `noecho`, `curs_set`, `keypad`).
* `bool alg_init_window(WINDOW *win, int w, int h)` — Initialise une sous-fenêtre spécifique avec ses dimensions.
* `void alg_destroy_window(WINDOW *win)` — Libère et détruit une fenêtre créée.
* `void alg_quit()` — Restaure le terminal et nettoie l'ensemble du contexte.

### Render & Buffer management

* `t_buffer *alg_create_buffer(int w, int h)` — Alloue une grille 2D hors-écran (caractères + attributs de couleur).
* `void alg_destroy_buffer(t_buffer *buf)` — Libère la mémoire associée à un buffer.
* `void alg_clear_buffer(t_buffer *buf)` — Réinitialise l'ensemble des cases du buffer (vide / espace).
* `void alg_clear_screen()` — Efface la fenêtre courante de l'écran.
* `void alg_present(WINDOW *win, t_buffer *buf)` — Copie le buffer vers la fenêtre et déclenche le rafraîchissement (`wrefresh`).

### Draw functions

* `bool alg_put_buffer(t_buffer *buf)` — Affiche l'intégralité du buffer directement sur l'écran principal (`stdscr`).
* `void alg_draw_pixel(t_buffer *buf, int x, int y, char ch, short color_pair)` — Écrit un caractère et sa couleur à des coordonnées données dans le buffer.
* `void alg_draw_line(t_buffer *buf, int x1, int y1, int x2, int y2, char ch, short color_pair)` — Trace une ligne selon l'algorithme de Bresenham.
* `void alg_draw_rect(t_buffer *buf, int x, int y, int w, int h, bool fill, char ch, short color_pair)` — Dessine un rectangle plein ou évidé.
* `void alg_draw_sprite(t_buffer *buf, int x, int y, const char **sprite, int w, int h)` — Copie une matrice de caractères (sprite) dans le buffer.
* `void alg_draw_text(t_buffer *buf, int x, int y, const char *text, short color_pair)` — Écrit une chaîne de caractères horizontalement.

### Input & Event handling

* `bool alg_poll_event(t_alg_event *event)` — Lit de manière non bloquante (`nodelay`) l'entrée clavier, les clics de souris ou le redimensionnement du terminal (`KEY_RESIZE`).

### Timing & Frame rate control

* `uint32_t alg_get_ticks()` — Retourne le temps écoulé depuis l'initialisation (en millisecondes).
* `void alg_delay(uint32_t ms)` — Fait une pause pour stabiliser le taux rafraîchissement d'affichage.

### Color & Attributes management

* `bool alg_init_color_pair(short pair_id, short fg, short bg)` — Déclare et enregistre une paire de couleur (texte / arrière-plan).
