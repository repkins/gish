int collectchanges(savechanges_t *changes, gamestate_t *save, char levelfilename[32]) {
	gamestate_t *prev_save;

    int gridmod_count = 0;
    int object_count = 0;
    int rope_count = 0;
    int particle_count = 0;
    int bond_count = 0;
    int temp_bond_count = 0;
	int total_count = 0;

    unsigned int i, j, t, numof;


	prev_save = malloc(sizeof *prev_save);
	changes->revision = loadsavefile(prev_save, levelfilename);
	changes->revision++;


    // gridmod
    for (i = 0; i < 256; i++)
    for (j = 0; j < 256; j++)
        if (prev_save->loaded == 1 && save->level_gridmod[i][j] != prev_save->level_gridmod[i][j])
            gridmod_count++;
		else if (prev_save->loaded == 0 && save->level_gridmod[i][j] != 0) {
			gridmod_count++;
		}

	changes->instructions.level_gridmod.numoftotal = gridmod_count;

    if (gridmod_count > 0) {
        changes->instructions.level_gridmod.payloads = malloc(sizeof(*changes->instructions.level_gridmod.payloads) * gridmod_count);

        t = 0;
        for (i = 0; i < 256; i++)
        for (j = 0; j < 256; j++)
            if (prev_save->loaded == 1 && save->level_gridmod[i][j] != prev_save->level_gridmod[i][j]) {
                changes->instructions.level_gridmod.payloads[t].x = j;
                changes->instructions.level_gridmod.payloads[t].y = i;
                changes->instructions.level_gridmod.payloads[t].value = &save->level_gridmod[i][j];

                t++;
            } else if (prev_save->loaded == 0 && save->level_gridmod[i][j] != 0) {
                changes->instructions.level_gridmod.payloads[t].x = j;
                changes->instructions.level_gridmod.payloads[t].y = i;
                changes->instructions.level_gridmod.payloads[t].value = &save->level_gridmod[i][j];

                t++;
            }
    } else {
		changes->instructions.level_gridmod.payloads = NULL;
    }


    // object
	numof = 512;

	for (i = 0; i < numof; i++)
		if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->object[i], &prev_save->object[i], sizeof save->object[i]) != 0))
			object_count++;

	changes->instructions.object.numoftotal = object_count;

	if (object_count > 0) {
		changes->instructions.object.payloads = malloc(sizeof(*changes->instructions.object.payloads) * object_count);

		t = 0;
		for (i = 0; i < numof; i++) 
			if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->object[i], &prev_save->object[i], sizeof save->object[i]) != 0)) {
				changes->instructions.object.payloads[t].objectnum = i;
				changes->instructions.object.payloads[t].value = &save->object[i];

				t++;
			}
	} else {
		changes->instructions.object.payloads = NULL;
	}


    // rope
	numof = 1024;

    for (i = 0; i < numof; i++)
		if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->rope[i], &prev_save->rope[i], sizeof save->rope[i]) != 0))
			rope_count++;

    changes->instructions.rope.numoftotal = rope_count;

    if (rope_count > 0) {
        changes->instructions.rope.payloads = malloc(sizeof(*changes->instructions.rope.payloads) * rope_count);

        t = 0;
        for (i = 0; i < numof; i++) 
            if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->rope[i], &prev_save->rope[i], sizeof save->rope[i]) != 0)) {
                changes->instructions.rope.payloads[t].ropenum = i;
                changes->instructions.rope.payloads[t].value = &save->rope[i];

                t++;
            }
    } else {
        changes->instructions.rope.payloads = NULL;
    }


    // particle
	numof = 16384;

    for (i = 0; i < numof; i++)
		if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->particle[i], &prev_save->particle[i], sizeof save->particle[i]) != 0))
			particle_count++;

    changes->instructions.particle.numoftotal = particle_count;

    if (particle_count > 0) {
        changes->instructions.particle.payloads = malloc(sizeof(*changes->instructions.particle.payloads) * particle_count);

        t = 0;
        for (i = 0; i < numof; i++) 
            if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->particle[i], &prev_save->particle[i], sizeof save->particle[i]) != 0)) {
                changes->instructions.particle.payloads[t].particlenum = i;
                changes->instructions.particle.payloads[t].value = &save->particle[i];

                t++;
            }
    } else {
        changes->instructions.particle.payloads = NULL;
    }


    // bond
	numof = 16384;

    for (i = 0; i < numof; i++)
		if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->bond[i], &prev_save->bond[i], sizeof save->bond[i]) != 0))
			bond_count++;

    changes->instructions.bond.numoftotal = bond_count;

    if (bond_count > 0){
        changes->instructions.bond.payloads = malloc(sizeof(*changes->instructions.bond.payloads) * bond_count);

        t = 0;
        for (i = 0; i < numof; i++) 
            if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->bond[i], &prev_save->bond[i], sizeof save->bond[i]) != 0)) {
                changes->instructions.bond.payloads[t].bondnum = i;
                changes->instructions.bond.payloads[t].value = &save->bond[i];

                t++;
            }
    } else {
        changes->instructions.bond.payloads = NULL;
    }


    // temp_bond
	numof = 8192;

    for (i = 0; i < numof; i++)
		if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->temp_bond[i], &prev_save->temp_bond[i], sizeof save->temp_bond[i]) != 0))
			temp_bond_count++;


    changes->instructions.temp_bond.numoftotal = temp_bond_count;

    if (temp_bond_count > 0) {
        changes->instructions.temp_bond.payloads = malloc(sizeof(*changes->instructions.temp_bond.payloads) * temp_bond_count);

        t = 0;
        for (i = 0; i < numof; i++) 
            if (prev_save->loaded == 0 || (prev_save->loaded == 1 && memcmp(&save->temp_bond[i], &prev_save->temp_bond[i], sizeof save->temp_bond[i]) != 0)) {
                changes->instructions.temp_bond.payloads[t].bondnum = i;
                changes->instructions.temp_bond.payloads[t].value = &save->temp_bond[i];

                t++;
            }
    } else {
        changes->instructions.temp_bond.payloads = NULL;
    }


    // total
	if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofobjects != prev_save->numofobjects))
		total_count++;
	if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofropes != prev_save->numofropes))
		total_count++;
	if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofparticles != prev_save->numofparticles))
		total_count++;
	if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofbonds != prev_save->numofbonds))
		total_count++;
	if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->temp_numofbonds != prev_save->temp_numofbonds))
		total_count++;

    changes->instructions.total.numoftotal = total_count;

    if (total_count > 0) {
        changes->instructions.total.payloads = malloc(sizeof(*changes->instructions.total.payloads) * total_count);

        t = 0;
        if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofobjects != prev_save->numofobjects)) {
            changes->instructions.total.payloads[t].totaltype = OBJECT;
            changes->instructions.total.payloads[t].value = &save->numofobjects;

            t++;
        }
        if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofropes != prev_save->numofropes)) {
            changes->instructions.total.payloads[t].totaltype = ROPE;
            changes->instructions.total.payloads[t].value = &save->numofropes;

            t++;
        }
        if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofparticles != prev_save->numofparticles)) {
            changes->instructions.total.payloads[t].totaltype = PARTICLE;
            changes->instructions.total.payloads[t].value = &save->numofparticles;

            t++;
        }
        if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->numofbonds != prev_save->numofbonds)) {
            changes->instructions.total.payloads[t].totaltype = BOND;
            changes->instructions.total.payloads[t].value = &save->numofbonds;

            t++;
        }
        if (prev_save->loaded == 0 || (prev_save->loaded == 1 && save->temp_numofbonds != prev_save->temp_numofbonds)) {
            changes->instructions.total.payloads[t].totaltype = TEMP_BOND;
            changes->instructions.total.payloads[t].value = &save->temp_numofbonds;

            t++;
        }
    } else {
        changes->instructions.total.payloads = NULL;
    }

	free(prev_save);

	return 0;
}

void applygamechanges(savechanges_t *changes, char levelfilename[32]) {
	gamestate_t *new_save;

    unsigned int t;
    unsigned int i, j;


	new_save = calloc(1, sizeof *new_save);
	loadsavefile(new_save, levelfilename);


    // gridmod
	if (new_save->loaded == 0) 
		memset(new_save->level_gridmod, 0, sizeof new_save->level_gridmod);

    for (t = 0; t < changes->instructions.level_gridmod.numoftotal; t++) {
        i = changes->instructions.level_gridmod.payloads[t].y;
        j = changes->instructions.level_gridmod.payloads[t].x;

        new_save->level_gridmod[i][j] = *changes->instructions.level_gridmod.payloads[t].value;
    }

    
    // object
    for (t = 0; t < changes->instructions.object.numoftotal; t++) {
        i = changes->instructions.object.payloads[t].objectnum;

        new_save->object[i] = *changes->instructions.object.payloads[t].value;
    }
    

    // rope
    for (t = 0; t < changes->instructions.rope.numoftotal; t++) {
        i = changes->instructions.rope.payloads[t].ropenum;

        new_save->rope[i] = *changes->instructions.rope.payloads[t].value;
    }


    // particle
    for (t = 0; t < changes->instructions.particle.numoftotal; t++) {
        i = changes->instructions.particle.payloads[t].particlenum;

        new_save->particle[i] = *changes->instructions.particle.payloads[t].value;
    }


    // bond
    for (t = 0; t < changes->instructions.bond.numoftotal; t++) {
        i = changes->instructions.bond.payloads[t].bondnum;

        new_save->bond[i] = *changes->instructions.bond.payloads[t].value;
    }


    // temp_bond
    for (t = 0; t < changes->instructions.temp_bond.numoftotal; t++) {
        i = changes->instructions.temp_bond.payloads[t].bondnum;

        new_save->temp_bond[i] = *changes->instructions.temp_bond.payloads[t].value;
    }


    // total
    for (t = 0; t < changes->instructions.total.numoftotal; t++)
        switch (changes->instructions.total.payloads[t].totaltype) {
            case OBJECT: 
                new_save->numofobjects = *changes->instructions.total.payloads[t].value;
            break;
            case ROPE: 
                new_save->numofropes = *changes->instructions.total.payloads[t].value;
            break;
            case PARTICLE: 
                new_save->numofparticles = *changes->instructions.total.payloads[t].value;
            break;
            case BOND: 
                new_save->numofbonds = *changes->instructions.total.payloads[t].value;
            break;
            case TEMP_BOND: 
                new_save->temp_numofbonds = *changes->instructions.total.payloads[t].value;
            break;
        }

	
	new_save->loaded = 1;


	savegamefile(new_save, levelfilename, changes->revision);


	free(new_save);
}

void savegamechanges(savechanges_t *changes, char levelfilename[32]) {
    int changeddir;
	char changesfilename[48];
	char reportfilename[48];

    unsigned int t;

	FILE *fp2;

	size_t size_gridmod = 0;
	size_t size_object = 0;
	size_t size_rope = 0;
	size_t size_particle = 0;
	size_t size_bond = 0;
	size_t size_temp_bond = 0;
	size_t size_total = 0;

    size_t size_changes = 0;


	changeddir=chdir("saves");

	sprintf(changesfilename, "%s.%u.sch", levelfilename, changes->revision);

	if ((fp=fopen(changesfilename,"wb")) != NULL) {

        fwrite2(&changes->revision, sizeof changes->revision, 1, fp);


        // gridmod
        fwrite2(&changes->instructions.level_gridmod.numoftotal, sizeof changes->instructions.level_gridmod.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.level_gridmod.numoftotal; t++) {
            fwrite2(&changes->instructions.level_gridmod.payloads[t].y, sizeof changes->instructions.level_gridmod.payloads[t].y, 1, fp);
            fwrite2(&changes->instructions.level_gridmod.payloads[t].x, sizeof changes->instructions.level_gridmod.payloads[t].x, 1, fp);
            fwrite2(changes->instructions.level_gridmod.payloads[t].value, sizeof *changes->instructions.level_gridmod.payloads[t].value, 1, fp);

            size_gridmod += sizeof changes->instructions.level_gridmod.payloads[t].y;
            size_gridmod += sizeof changes->instructions.level_gridmod.payloads[t].x;
            size_gridmod += sizeof *changes->instructions.level_gridmod.payloads[t].value;
        }


        // object
        fwrite2(&changes->instructions.object.numoftotal, sizeof changes->instructions.object.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.object.numoftotal; t++) {
            fwrite2(&changes->instructions.object.payloads[t].objectnum, sizeof changes->instructions.object.payloads[t].objectnum, 1, fp);
            fwrite2(changes->instructions.object.payloads[t].value, sizeof *changes->instructions.object.payloads[t].value, 1, fp);

            size_object += sizeof changes->instructions.object.payloads[t].objectnum;
            size_object += sizeof *changes->instructions.object.payloads[t].value;
        }

        
        // rope
        fwrite2(&changes->instructions.rope.numoftotal, sizeof changes->instructions.rope.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.rope.numoftotal; t++) {
            fwrite2(&changes->instructions.rope.payloads[t].ropenum, sizeof changes->instructions.rope.payloads[t].ropenum, 1, fp);
            fwrite2(changes->instructions.rope.payloads[t].value, sizeof *changes->instructions.rope.payloads[t].value, 1, fp);

            size_rope += sizeof changes->instructions.rope.payloads[t].ropenum;
            size_rope += sizeof *changes->instructions.rope.payloads[t].value;
        }


        // particle
        fwrite2(&changes->instructions.particle.numoftotal, sizeof changes->instructions.particle.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.particle.numoftotal; t++) {
            fwrite2(&changes->instructions.particle.payloads[t].particlenum, sizeof changes->instructions.particle.payloads[t].particlenum, 1, fp);
            fwrite2(changes->instructions.particle.payloads[t].value, sizeof *changes->instructions.particle.payloads[t].value, 1, fp);

            size_particle += sizeof changes->instructions.particle.payloads[t].particlenum;
            size_particle += sizeof *changes->instructions.particle.payloads[t].value;
        }


        // bond
        fwrite2(&changes->instructions.bond.numoftotal, sizeof changes->instructions.bond.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.bond.numoftotal; t++) {
            fwrite2(&changes->instructions.bond.payloads[t].bondnum, sizeof changes->instructions.bond.payloads[t].bondnum, 1, fp);
            fwrite2(changes->instructions.bond.payloads[t].value, sizeof *changes->instructions.bond.payloads[t].value, 1, fp);

            size_bond += sizeof changes->instructions.bond.payloads[t].bondnum;
            size_bond += sizeof *changes->instructions.bond.payloads[t].value;
        }


        // temp_bond
        fwrite2(&changes->instructions.temp_bond.numoftotal, sizeof changes->instructions.temp_bond.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.temp_bond.numoftotal; t++) {
            fwrite2(&changes->instructions.temp_bond.payloads[t].bondnum, sizeof changes->instructions.temp_bond.payloads[t].bondnum, 1, fp);
            fwrite2(changes->instructions.temp_bond.payloads[t].value, sizeof *changes->instructions.temp_bond.payloads[t].value, 1, fp);

            size_temp_bond += sizeof changes->instructions.temp_bond.payloads[t].bondnum;
            size_temp_bond += sizeof *changes->instructions.temp_bond.payloads[t].value;
        }


        // total
        fwrite2(&changes->instructions.total.numoftotal, sizeof changes->instructions.total.numoftotal, 1, fp);
        for (t = 0; t < changes->instructions.total.numoftotal; t++) {
            fwrite2(&changes->instructions.total.payloads[t].totaltype, sizeof changes->instructions.total.payloads[t].totaltype, 1, fp);
            fwrite2(changes->instructions.total.payloads[t].value, sizeof *changes->instructions.total.payloads[t].value, 1, fp);

            size_total += sizeof changes->instructions.total.payloads[t].totaltype;
            size_total += sizeof *changes->instructions.total.payloads[t].value;
        }


		fclose(fp);
    }


	sprintf(reportfilename, "%s.%u.csv", levelfilename, changes->revision);

	if ((fp2=fopen(reportfilename,"w")) != NULL) {

		fprintf(fp2, "Type       , Count, Bytes \n\r");

		fprintf(fp2, " gridmod   , %+5u, %+5u \n\r", changes->instructions.level_gridmod.numoftotal, size_gridmod);
        fprintf(fp2, " object    , %+5u, %+5u \n\r", changes->instructions.object.numoftotal, size_object);
        fprintf(fp2, " rope      , %+5u, %+5u \n\r", changes->instructions.rope.numoftotal, size_rope);
        fprintf(fp2, " particle  , %+5u, %+5u \n\r", changes->instructions.particle.numoftotal, size_particle);
        fprintf(fp2, " bond      , %+5u, %+5u \n\r", changes->instructions.bond.numoftotal, size_bond);
        fprintf(fp2, " temp_bond , %+5u, %+5u \n\r", changes->instructions.temp_bond.numoftotal, size_temp_bond);
        fprintf(fp2, " total     , %+5u, %+5u \n\r", changes->instructions.total.numoftotal, size_total);


		fclose(fp2);
	}


    size_changes += size_gridmod;
    size_changes += size_object;
    size_changes += size_rope;
    size_changes += size_particle;
    size_changes += size_bond;
    size_changes += size_temp_bond;
    size_changes += size_total;


	if (changeddir==0)
		chdir("..");
}


void freechanges(savechanges_t *changes) {
	if (changes->instructions.level_gridmod.payloads != NULL)
		free(changes->instructions.level_gridmod.payloads);

    if (changes->instructions.object.payloads != NULL)    
	    free(changes->instructions.object.payloads);

    if (changes->instructions.rope.payloads != NULL)
	    free(changes->instructions.rope.payloads);

    if (changes->instructions.particle.payloads != NULL)
	    free(changes->instructions.particle.payloads);

    if (changes->instructions.bond.payloads != NULL)
	    free(changes->instructions.bond.payloads);

    if (changes->instructions.temp_bond.payloads != NULL)
	    free(changes->instructions.temp_bond.payloads);
	
    if (changes->instructions.total.payloads != NULL)
	    free(changes->instructions.total.payloads);
}