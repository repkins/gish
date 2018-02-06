
unsigned int loadsavefile(gamestate_t *save, char levelfilename[32]) {
	int changeddir;
	char savefilename[48];
	unsigned int revision = 0;

	changeddir=chdir("saves");

	strcpy(savefilename, levelfilename);
	strcat(savefilename, ".sve");
	if ((fp=fopen(savefilename,"rb"))!=NULL) {

		fread2(&revision, sizeof revision, 1, fp);

		fread2(save->level_gridmod, sizeof save->level_gridmod, 1, fp);

		fread2(save->object, sizeof save->object, 1, fp);
		fread2(&save->numofobjects, sizeof save->numofobjects, 1, fp);

		fread2(save->rope, sizeof save->rope, 1, fp);
		fread2(&save->numofropes, sizeof save->numofropes, 1, fp);

		fread2(save->particle, sizeof save->particle, 1, fp);
		fread2(&save->numofparticles, sizeof save->numofparticles, 1, fp);

		fread2(save->bond, sizeof save->bond, 1, fp);
		fread2(&save->numofbonds, sizeof save->numofbonds, 1, fp);

		fread2(save->temp_bond, sizeof save->temp_bond, 1, fp);
		fread2(&save->temp_numofbonds, sizeof save->temp_numofbonds, 1, fp);
		

		fclose(fp);
		
		save->loaded = 1;
	} else {
		save->loaded = 0;
	}

	if (changeddir==0)
		chdir("..");

	return revision;
}

void savegamefile(gamestate_t *save, char levelfilename[32], unsigned int revision) {
	int changeddir;
	char savefilename[48];

	changeddir=chdir("saves");
	
	strcpy(savefilename, levelfilename);
	strcat(savefilename, ".sve");
	if ((fp=fopen(savefilename,"wb"))!=NULL) {
		
		fwrite2(&revision, sizeof revision, 1, fp);

		fwrite2(save->level_gridmod, sizeof save->level_gridmod, 1, fp);

		fwrite2(save->object, sizeof save->object, 1, fp);
		fwrite2(&save->numofobjects, sizeof save->numofobjects, 1, fp);

		fwrite2(save->rope, sizeof save->rope, 1, fp);
		fwrite2(&save->numofropes, sizeof save->numofropes, 1, fp);

		fwrite2(save->particle, sizeof save->particle, 1, fp);
		fwrite2(&save->numofparticles, sizeof save->numofparticles, 1, fp);

		fwrite2(save->bond, sizeof save->bond, 1, fp);
		fwrite2(&save->numofbonds, sizeof save->numofbonds, 1, fp);

		fwrite2(save->temp_bond, sizeof save->temp_bond, 1, fp);
		fwrite2(&save->temp_numofbonds, sizeof save->temp_numofbonds, 1, fp);


		fclose(fp);
	}
	
	if (changeddir==0)
		chdir("..");
}
