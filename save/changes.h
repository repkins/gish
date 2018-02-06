int collectchanges(savechanges_t *changes, gamestate_t *save, char levelfilename[32]);
void applygamechanges(savechanges_t *changes, char levelfilename[32]);
void savegamechanges(savechanges_t *changes, char levelfilename[32]);

void freechanges(savechanges_t *changes);
