
int savethegame(void);
void loadthegame(void);


typedef struct {
	int level_gridmod[256][256];
	
	struct object_t object[512];
	int numofobjects;

	struct rope_t rope[1024];
	int numofropes;

	struct particle_t particle[16384];
	int numofparticles;

	struct bond_t bond[16384];
	int numofbonds;
	
	struct temp_bond_t temp_bond[8192];
	int temp_numofbonds;

	unsigned char loaded;
} gamestate_t;

typedef struct {
	unsigned int revision;

	struct {
		struct {
			int numoftotal;
			struct {
				int x;
				int y;
				int *value;
			} *payloads;
		} level_gridmod;

		struct {
			int numoftotal;
			struct {
				int objectnum;
				struct object_t *value;
			} *payloads;
		} object;

		struct {
			int numoftotal;
			struct {
				int ropenum;
				struct rope_t *value;
			} *payloads;
		} rope;

		struct {
			int numoftotal;
			struct {
				int particlenum;
				struct particle_t *value;
			} *payloads;
		} particle;

		struct {
			int numoftotal;
			struct {
				int bondnum;
				struct bond_t *value;
			} *payloads;
		} bond;

		struct {
			int numoftotal;
			struct {
				int bondnum;
				struct temp_bond_t *value;
			} *payloads;
		} temp_bond;
		
		struct {
			int numoftotal;
			struct {
				enum {
					OBJECT,
					ROPE,
					PARTICLE,
					BOND,
					TEMP_BOND
				} totaltype;
				int *value;
			} *payloads;
		} total;
	} instructions;
} savechanges_t;
