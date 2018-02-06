
int savethegame(void) {
	gamestate_t *save;
	savechanges_t changes;

	int err;


	save = malloc(sizeof *save);

	memcpy(save->level_gridmod, level.gridmod, sizeof level.gridmod);

	memcpy(save->object, object, sizeof object);
	save->numofobjects = numofobjects;

	memcpy(save->rope, rope, sizeof rope);
	save->numofropes = numofropes;

	memcpy(save->particle, particle, sizeof particle);
	save->numofparticles = numofparticles;

	memcpy(save->bond, bond, sizeof bond);
	save->numofbonds = numofbonds;

	memcpy(save->temp_bond, physicstemp.bond, sizeof physicstemp.bond);
	save->temp_numofbonds = physicstemp.numofbonds;

	save->loaded = 1;


	err = collectchanges(&changes, save, editor.filename);
	
	if (err == 0) {
		savegamechanges(&changes, editor.filename);
		applygamechanges(&changes, editor.filename);
	}

	free(save);
	freechanges(&changes);

	if (err != 0) {
		return 1;
	} else {
		return 0;
	}
}

void loadthegame(void) {
	gamestate_t *save = malloc(sizeof *save);

	loadsavefile(save, editor.filename);

	if (save->loaded == 1) {

		memcpy(level.gridmod, save->level_gridmod, sizeof save->level_gridmod);

		memcpy(object, save->object, sizeof save->object);
		numofobjects = save->numofobjects;

		memcpy(rope, save->rope, sizeof save->rope);
		numofropes = save->numofropes;

		memcpy(particle, save->particle, sizeof save->particle);
		numofparticles = save->numofparticles;

		memcpy(bond, save->bond, sizeof save->bond);
		numofbonds = save->numofbonds;

		memcpy(physicstemp.bond, save->temp_bond, sizeof save->temp_bond);
		physicstemp.numofbonds = save->temp_numofbonds;		
	}
	

	free(save);
}
