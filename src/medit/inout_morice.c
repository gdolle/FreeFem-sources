/****************************************************************************/
/* This file is part of FreeFEM.                                            */
/*                                                                          */
/* FreeFEM is free software: you can redistribute it and/or modify          */
/* it under the terms of the GNU Lesser General Public License as           */
/* published by the Free Software Foundation, either version 3 of           */
/* the License, or (at your option) any later version.                      */
/*                                                                          */
/* FreeFEM is distributed in the hope that it will be useful,               */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/* GNU Lesser General Public License for more details.                      */
/*                                                                          */
/* You should have received a copy of the GNU Lesser General Public License */
/* along with FreeFEM. If not, see <http://www.gnu.org/licenses/>.          */
/****************************************************************************/
/* SUMMARY : ...                                                            */
/* LICENSE : LGPLv3                                                         */
/* ORG     : LJLL Universite Pierre et Marie Curie, Paris, FRANCE           */
/* AUTHORS : Pascal Frey                                                    */
/* E-MAIL  : pascal.frey@sorbonne-universite.fr                             */

#ifdef __cplusplus
extern "C" {
#endif

#include "medit.h"
#include "libmeshb7.h"
#include "extern.h"
#include "string.h"
#include "eigenv.h"

static int debug = 0;
void getline_number (char *nature, int *nb) {
	char data[256];
	char *tictac;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) {
		printf("problem in reading the number of %s\n", nature);
		exit(1);
	} else {
		*nb = atoi(tictac);
		if (debug) fprintf(stdout, "Number of %s %i \n", nature, *nb);
	}
}

void getline_1int (char *nature, int *nbint) {
	char data[256];
	char *tictac;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) {
		printf("problem in reading the %s", nature);
		exit(1);
	}

	*nbint = atoi(tictac);
}

void getline_1intfirst (char *nature, int *nbint) {
	char data[256];
	char *tictac;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) {
		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");
	}

	if (tictac == NULL) {
		printf("problem in reading the first %s", nature);
		exit(1);
	}

	*nbint = atoi(tictac);
}

void getline_popen_vertex (int ddim, double *c, int *ref) {
	char data[256];
	char *tictac;
	int i;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	c[0] = strtod(data, &tictac);

	for (i = 1; i < ddim; i++)
		c[i] = strtod(tictac, &tictac);

	*ref = atoi(tictac);
}

void getline_popen_firstvertex (int ddim, double *c, int *ref) {
	char data[256];
	char *tictac;
	int i;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	c[0] = strtod(data, &tictac);

	for (i = 1; i < ddim; i++)
		c[i] = strtod(tictac, &tictac);

	*ref = atoi(tictac);
}

void getline_popen_elem (int ddim, int *v, int *ref) {
	char data[256];
	char *tictac;
	int i;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) printf("problem: in reading element");

	for (i = 0; i < ddim; i++) {
		v[i] = atoi(tictac);
		tictac = strtok(NULL, " \n");
	}

	*ref = atoi(tictac);
}

void getline_popen_firstelem (int ddim, int *v, int *ref) {
	char data[256];
	char *tictac;
	int i;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");

	if (tictac == NULL) {
		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");
	}

	if (tictac == NULL) printf("problem in reading the first element");

	for (i = 0; i < ddim; i++) {
		v[i] = atoi(tictac);
		tictac = strtok(NULL, " \n");
	}

	*ref = atoi(tictac);
}

void getline_popen_edge (int *v0, int *v1, int *ref) {
	char data[256];
	char *tictac;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) printf("problem: in reading edges");

	*v0 = atoi(tictac);
	tictac = strtok(NULL, " \n");

	*v1 = atoi(tictac);
	tictac = strtok(NULL, " \n");

	*ref = atoi(tictac);
}

void getline_popen_firstedge (int *v0, int *v1, int *ref) {
	char data[256];
	char *tictac;
	char *res;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	if (debug) fprintf(stdout, "data edge %s\n", data);

	tictac = strtok(data, " \n");
	if (tictac == NULL) {
		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");
	}

	if (tictac == NULL) printf("problem: in reading first edges\n");

	*v0 = atoi(tictac);
	tictac = strtok(NULL, " \n");

	*v1 = atoi(tictac);
	tictac = strtok(NULL, " \n");

	*ref = atoi(tictac);
}

void getline_popen_elemnoref (char *nature, int ddim, int *v) {
	char data[256];
	char *tictac, *res;
	int i;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) printf("problem: in reading %s\n", nature);

	for (i = 0; i < ddim; i++) {
		v[i] = atoi(tictac);
		tictac = strtok(NULL, " \n");
	}

	if (tictac != NULL) printf("problem: in reading %s\n", nature);
}

void getline_popen_firstelemnoref (char *nature, int ddim, int *v) {
	char data[256];
	char *tictac, *res;
	int i;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");

	if (tictac == NULL) {
		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");
	}

	if (tictac == NULL) printf("problem in reading the first %s\n", nature);

	for (i = 0; i < ddim; i++) {
		v[i] = atoi(tictac);
		tictac = strtok(NULL, " \n");
	}
}

void getline_popen_firstdouble (char *nature, int ddim, double *v) {
	char data[256];
	char *tictac, *res;
	int i;
	char *tictac2;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");

	tictac2 = strtok(data, " \n");

	if (tictac2 == NULL) {
		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
	}

	v[0] = strtod(data, &tictac);

	for (i = 1; i < ddim; i++) {
		v[i] = strtod(tictac, &tictac);
	}
}

void getline_popen_double (char *nature, int ddim, double *v) {
	char data[256];
	char *tictac, *res;
	int i;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	v[0] = strtod(data, &tictac);

	for (i = 1; i < ddim; i++) {
		v[i] = strtod(tictac, &tictac);
	}
}

/*   function for loadsol_popen   */
void read_TypeSizeTyptab (char *nature, int *type, int *size, int *typtab) {
	char data[256];
	char *tictac, *res;
	int i;
	int tmptype;
	int tmpsize;

	res = fgets(data, 256, stdin);
	if (res == NULL) printf("fgets error\n");
	tictac = strtok(data, " \n");
	if (tictac == NULL) printf("problem: in reading %s", nature);

	tmptype = atoi(tictac);
	assert(tmptype <= GmfMaxTyp);

	tictac = strtok(NULL, " \n");
	tmpsize = 0;

	for (i = 0; i < tmptype; i++) {
		typtab[i] = atoi(tictac);
		if (debug) printf("typtab[%i]=%i\n", i, typtab[i]);

		tmpsize += typtab[i];
		tictac = strtok(NULL, " \n");
	}

	*size = tmpsize;
	*type = tmptype;
}

int loadMesh_popen (pMesh mesh) {
	pPoint ppt;
	pEdge pr;
	pTriangle pt;
	pQuad pq;
	pTetra ptet;
	pHexa ph;
	double d, dn[3];
	float *n;
	int i, ia, ib, ref, is=0, k, disc=0, nn=0, nt=0, nq=0;
	char data[256];
	char *natureread, *res;
	int loopdebug;
	int vatn[2];
	int tvatn[3];

	/* parse keywords */
	mesh->np = 0;
	mesh->nt = 0;
	mesh->nq = 0;
	mesh->ntet = 0;
	mesh->nhex = 0;
	mesh->nc = 0;
	mesh->nr = 0;
	mesh->na = 0;
	mesh->nri = 0;
	mesh->nre = 0;
	mesh->nvn = 0;
	mesh->ntg = 0;
	mesh->ne = mesh->nt + mesh->nq + mesh->ntet + mesh->nhex;

	loopdebug = -1;

	while (!feof(stdin)) {
		char *tictac;

		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");

		loopdebug = loopdebug + 1;
		if (tictac == NULL) continue;

		if (!strncmp(tictac, "MeshVersionFormatted", 20)) {
			/* read mesh format */
			natureread = "MeshVersionFormatted";
			getline_number(natureread, &(mesh->ver));
		} else if (!strncmp(tictac, "Dimension", 9)) {
			/* read mesh dimension */
			natureread = "Dimension";
			getline_number(natureread, &(mesh->dim));
			/*control of the dimension*/
			if ((mesh->dim != 2) && (mesh->dim != 3))
				printf("the dimension is not correct");
		} else if (!strncmp(tictac, "Vertices", 8)) {
			/* read mesh vetices */
			natureread = "Vertices";
			getline_number(natureread, &(mesh->np));
			/*  Allocation of array of vertices  */
			if (ddebug) printf("allocate %d points\n", mesh->np);

			mesh->point = (pPoint)M_calloc(mesh->np + 1, sizeof(Point), "zaldy1.point");
			assert(mesh->point);

			/* read the first vertex */

			k = 1;
			ppt = &mesh->point[k];
			getline_popen_firstvertex(mesh->dim, ppt->c, &ref);

			ppt->ref = ref & 0x7fff;
			ppt->tag = M_UNUSED;

			/* read the other vertices */
			for (k = 2; k <= mesh->np; k++) {
				ppt = &mesh->point[k];

				getline_popen_vertex(mesh->dim, ppt->c, &ref);
				ppt->ref = ref & 0x7fff;
				ppt->tag = M_UNUSED;
			}
		} else if (!strncmp(tictac, "Triangles", 9)) {
			natureread = "Triangles";
			getline_number(natureread, &(mesh->nt));
			/*  Allocation of array of triangles  */
			if (ddebug) printf("allocate %d tria\n", mesh->nt);

			mesh->tria = (pTriangle)M_calloc(mesh->nt + 1, sizeof(Triangle), "zaldy1.tria");
			assert(mesh->tria);

			/* read the first triangle */

			k = 1;
			pt = &mesh->tria[k];
			getline_popen_firstelem(3, pt->v, &ref);

			pt->ref = ref & 0x7fff;

			for (i = 0; i < 3; i++) {
				if (pt->v[i] < 1 || pt->v[i] > mesh->np) {
					disc++;
					pt->v[0] = 0;
					break;
				} else {
					ppt = &mesh->point[pt->v[i]];
					ppt->tag &= ~M_UNUSED;
				}
			}

			/* read mesh triangles */

			for (k = 2; k <= mesh->nt; k++) {
				pt = &mesh->tria[k];
				getline_popen_elem(3, pt->v, &ref);

				pt->ref = ref & 0x7fff;

				for (i = 0; i < 3; i++) {
					if (pt->v[i] < 1 || pt->v[i] > mesh->np) {
						disc++;
						pt->v[0] = 0;
						break;
					} else {
						ppt = &mesh->point[pt->v[i]];
						ppt->tag &= ~M_UNUSED;
					}
				}
			}
		} else if (!strncmp(tictac, "Quadrilaterals", 14)) {
			natureread = "Quadrilaterals";
			getline_number(natureread, &(mesh->nq));
			/*  allocation  */
			if (ddebug) printf("allocate %d quad\n", mesh->nq);

			if (mesh->nq) {
				mesh->quad = (pQuad)M_calloc(mesh->nq + 1, sizeof(Quad), "zaldy1.quad");
				assert(mesh->quad);
			}

			k = 1;
			pq = &mesh->quad[k];
			getline_popen_firstelem(4, pq->v, &ref);
			pq->ref = ref & 0x7fff;

			for (i = 0; i < 4; i++) {
				if (pq->v[i] < 1 || pq->v[i] > mesh->np) {
					disc++;
					pq->v[0] = 0;
					break;
				} else {
					ppt = &mesh->point[pq->v[i]];
					ppt->tag &= ~M_UNUSED;
				}
			}

			for (k = 2; k <= mesh->nq; k++) {
				pq = &mesh->quad[k];
				getline_popen_elem(4, pq->v, &ref);
				pq->ref = ref & 0x7fff;

				for (i = 0; i < 4; i++) {
					if (pq->v[i] < 1 || pq->v[i] > mesh->np) {
						disc++;
						pq->v[0] = 0;
						break;
					} else {
						ppt = &mesh->point[pq->v[i]];
						ppt->tag &= ~M_UNUSED;
					}
				}
			}
		} else if (!strncmp(tictac, "Tetrahedra", 10)) {
			natureread = "Tetrahedra";
			getline_number(natureread, &(mesh->ntet));
			/*  allocation de la memoire  */
			if (mesh->ntet) {
				if (ddebug) printf("allocate %d tetra\n", mesh->ntet);

				mesh->tetra = (pTetra)M_calloc(mesh->ntet + 1, sizeof(Tetra), "zaldy1.tetra");
				assert(mesh->tetra);
			}

			k = 1;
			ptet = &mesh->tetra[k];
			getline_popen_elem(4, ptet->v, &ref);
			ptet->ref = ref & 0x7fff;

			for (i = 0; i < 4; i++) {
				if (ptet->v[i] < 1 || ptet->v[i] > mesh->np) {
					disc++;
					ptet->v[0] = 0;
					break;
				} else {
					ppt = &mesh->point[ptet->v[i]];
					ppt->tag &= ~M_UNUSED;
				}
			}

			for (k = 2; k <= mesh->ntet; k++) {
				ptet = &mesh->tetra[k];
				getline_popen_elem(4, ptet->v, &ref);
				ptet->ref = ref & 0x7fff;

				for (i = 0; i < 4; i++) {
					if (ptet->v[i] < 1 || ptet->v[i] > mesh->np) {
						disc++;
						ptet->v[0] = 0;
						break;
					} else {
						ppt = &mesh->point[ptet->v[i]];
						ppt->tag &= ~M_UNUSED;
					}
				}
			}
		}
		/* mesh hexahedra */
		else if (!strncmp(tictac, "Hexahedra", 9)) {
			natureread = "Hexahedra";
			getline_number(natureread, &(mesh->nhex));
			/* allocation de la memoire   */
			if (ddebug) printf("allocate %d hexa\n", mesh->nhex);

			mesh->hexa = (pHexa)M_calloc(mesh->nhex + 1, sizeof(Hexa), "zaldy1.hexa");
			assert(mesh->hexa);

			k = 1;
			ph = &mesh->hexa[k];
			getline_popen_firstelem(8, ph->v, &ref);

			ph->ref = ref & 0x7fff;

			for (i = 0; i < 8; i++) {
				if (ph->v[i] < 1 || ph->v[i] > mesh->np) {
					disc++;
					ph->v[0] = 0;
					break;
				} else {
					ppt = &mesh->point[ph->v[i]];
					ppt->tag &= ~M_UNUSED;
				}
			}

			for (k = 2; k <= mesh->nhex; k++) {
				ph = &mesh->hexa[k];
				getline_popen_elem(8, ph->v, &ref);

				ph->ref = ref & 0x7fff;

				for (i = 0; i < 8; i++) {
					if (ph->v[i] < 1 || ph->v[i] > mesh->np) {
						disc++;
						ph->v[0] = 0;
						break;
					} else {
						ppt = &mesh->point[ph->v[i]];
						ppt->tag &= ~M_UNUSED;
					}
				}
			}
		}
		/* mesh corners */
		else if (!strncmp(tictac, "Corners", 7)) {
			natureread = "Corners";
			getline_number(natureread, &(mesh->nc));

			res = fgets(data, 256, stdin);
			if (res == NULL) printf("fgets error\n");
			if (tictac == NULL) {
				res = fgets(data, 256, stdin);
				if (res == NULL) printf("fgets error\n");
				tictac = strtok(data, " \n");
			}

			if (tictac == NULL) printf("problem in reading the first corner");

			tictac = strtok(data, " \n");
			is = atoi(tictac);

			if (is < 1 || is > mesh->np) {
				disc++;
			} else {
				ppt = &mesh->point[is];
				ppt->tag |= M_CORNER;
				ppt->tag &= ~M_UNUSED;
			}

			for (k = 2; k <= mesh->nc; k++) {
				res = fgets(data, 256, stdin);
				if (res == NULL) printf("fgets error\n");
				tictac = strtok(data, " \n");
				is = atoi(tictac);
				if (is < 1 || is > mesh->np) {
					disc++;
				} else {
					ppt = &mesh->point[is];
					ppt->tag |= M_CORNER;
					ppt->tag &= ~M_UNUSED;
				}
			}
		}
		/* required vertices */
		else if (!strncmp(tictac, "RequiredVertices", 12)) {
			natureread = "RequiredVertices";
			getline_number(natureread, &(mesh->nr));

			res = fgets(data, 256, stdin);
			if (res == NULL) printf("fgets error\n");
			if (tictac == NULL) {
				res = fgets(data, 256, stdin);
				if (res == NULL) printf("fgets error\n");
				tictac = strtok(data, " \n");
			}

			if (tictac == NULL) printf("problem in reading the first RequiredVertex");

			tictac = strtok(data, " \n");
			is = atoi(tictac);

			if (is < 1 || is > mesh->np) {
				disc++;
			} else {
				ppt = &mesh->point[is];
				ppt->tag |= M_REQUIRED;
				ppt->tag &= ~M_UNUSED;
			}

			for (k = 2; k <= mesh->nr; k++) {
				res = fgets(data, 256, stdin);
				if (res == NULL) printf("fgets error\n");
				tictac = strtok(data, " \n");
				is = atoi(tictac);
				if (is < 1 || is > mesh->np) {
					disc++;
				} else {
					ppt = &mesh->point[is];
					ppt->tag |= M_REQUIRED;
					ppt->tag &= ~M_UNUSED;
				}
			}
		}
		/* mesh edges */
		else if (!strncmp(tictac, "Edges", 5)) {
			natureread = "Edges";
			getline_number(natureread, &(mesh->na));
			fprintf(stdout, "Number of %s %i \n", natureread, mesh->na);
			/*  allocation memoire  */

			if (ddebug) printf("allocate %d edges\n", mesh->na);

			mesh->edge = (pEdge)M_calloc(mesh->na + 1, sizeof(Edge), "zaldy1.edge");
			assert(mesh->edge);

			k = 1;
			getline_popen_firstedge(&ia, &ib, &ref);
			if (ia < 1 || ia > mesh->np || ib < 1 || ib > mesh->np) {
				disc++;
			} else {
				pr = &mesh->edge[k];
				pr->v[0] = ia;
				pr->v[1] = ib;
				pr->ref = ref & 0x7fff;
				pr->tag = !pr->ref ? M_NOTAG : M_TAG;
				ppt = &mesh->point[ia];
				ppt->tag &= ~M_UNUSED;
				ppt = &mesh->point[ib];
				ppt->tag &= ~M_UNUSED;
			}

			for (k = 2; k <= mesh->na; k++) {
				getline_popen_edge(&ia, &ib, &ref);
				if (ia < 1 || ia > mesh->np || ib < 1 || ib > mesh->np) {
					disc++;
				} else {
					pr = &mesh->edge[k];
					pr->v[0] = ia;
					pr->v[1] = ib;
					pr->ref = ref & 0x7fff;
					pr->tag = !pr->ref ? M_NOTAG : M_TAG;
					ppt = &mesh->point[ia];
					ppt->tag &= ~M_UNUSED;
					ppt = &mesh->point[ib];
					ppt->tag &= ~M_UNUSED;
				}
			}
		}
		/* mesh ridges */
		else if (!strcmp(tictac, "Ridges")) {
			natureread = "Ridges";
			getline_number(natureread, &(mesh->nri));

			getline_1intfirst(natureread, &is);
			if (is < 1 || is > mesh->na) {
				disc++;
			} else {
				pr = &mesh->edge[is];
				pr->tag |= M_RIDGE;
			}

			for (k = 2; k <= mesh->nri; k++) {
				getline_1int(natureread, &is);
				if (is < 1 || is > mesh->na) {
					disc++;
				} else {
					pr = &mesh->edge[is];
					pr->tag |= M_RIDGE;
				}
			}
		}
		/* required edges */
		else if (!strncmp(tictac, "RequiredEdges", 13)) {
			natureread = "RequiredEdges";
			getline_number(natureread, &(mesh->nre));

			getline_1intfirst(natureread, &is);
			if (is < 1 || is > mesh->na) {
				disc++;
			} else {
				pr = &mesh->edge[is];
				pr->tag |= M_REQUIRED;
			}

			for (k = 2; k <= mesh->nre; k++) {
				getline_1int(natureread, &is);
				if (is < 1 || is > mesh->na) {
					disc++;
				} else {
					pr = &mesh->edge[is];
					pr->tag |= M_REQUIRED;
				}
			}
		}
		/* mesh normals */
		else if (!strncmp(tictac, "Normals", 7)) {
			natureread = "Normals";
			getline_number(natureread, &(mesh->nvn));

			/*  allocation  */
			if (!mesh->ntg) {
				mesh->extra = (pExtra)M_calloc(1, sizeof(Extra), "zaldy1.extra");
				assert(mesh->extra);
			}

			mesh->extra->n = (float *)M_calloc(3 * mesh->nvn + 1, sizeof(float), "inmesh");
			assert(mesh->extra->n);

			k = 1;
			n = &mesh->extra->n[3 * (k - 1) + 1];
			getline_popen_firstdouble(natureread, 3, dn);

			n[0] = dn[0];
			n[1] = dn[1];
			n[2] = dn[2];
			d = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
			if (d > 0.0) {
				d = 1.0 / sqrt(d);
				n[0] *= d;
				n[1] *= d;
				n[2] *= d;
			}

			for (k = 2; k <= mesh->nvn; k++) {
				n = &mesh->extra->n[3 * (k - 1) + 1];
				getline_popen_double(natureread, 3, dn);
				n[0] = dn[0];
				n[1] = dn[1];
				n[2] = dn[2];

				d = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
				if (d > 0.0) {
					d = 1.0 / sqrt(d);
					n[0] *= d;
					n[1] *= d;
					n[2] *= d;
				}
			}
		} else if (!strncmp(tictac, "NormalAtVertices", 16)) {
			natureread = "NormalAtVertices";
			if (!mesh->nvn) {
				printf("The field Normal need to be reading before %s", natureread);
				exit(1);
			}

			/* normals at vertices */
			getline_number(natureread, &(mesh->extra->iv));
			mesh->extra->nv = (int *)M_calloc(mesh->np + 1, sizeof(int), "inmesh");
			assert(mesh->extra->nv);

			getline_popen_firstelemnoref(natureread, 2, vatn);
			nn = vatn[0];
			is = vatn[1];
			if (nn < 1 || nn > mesh->np)
				disc++;
			else
				mesh->extra->nv[nn] = is;

			for (k = 2; k <= mesh->extra->iv; k++) {
				getline_popen_elemnoref(natureread, 2, vatn);
				nn = vatn[0];
				is = vatn[1];
				if (nn < 1 || nn > mesh->np)
					disc++;
				else
					mesh->extra->nv[nn] = is;
			}
		} else if (!strncmp(tictac, "NormalAtTriangleVertices", 24)) {
			natureread = "NormalAtTriangleVertices";
			if (!mesh->nvn) {
				printf("The field Normal need to be reading before %s", natureread);
				exit(1);
			}

			/* normals at triangle vertices */
			getline_number(natureread, &(mesh->extra->it));
			mesh->extra->nt = (int *)M_calloc(3 * mesh->nt + 1, sizeof(int), "inmesh");
			assert(mesh->extra->nt);

			getline_popen_elemnoref(natureread, 3, tvatn);
			tvatn[0] = nt;
			tvatn[1] = is;
			tvatn[2] = nn;

			if (nt < 1 || nt > mesh->nt || is < 1 || is > 3 || nn < 1 || nn > mesh->nvn)
				disc++;
			else
				mesh->extra->nt[3 * (nt - 1) + is] = nn;

			for (k = 2; k <= mesh->extra->it; k++) {
				getline_popen_elemnoref(natureread, 3, tvatn);
				tvatn[0] = nt;
				tvatn[1] = is;
				tvatn[2] = nn;

				if (nt < 1 || nt > mesh->nt || is < 1 || is > 3 || nn < 1 || nn > mesh->nvn)
					disc++;
				else
					mesh->extra->nt[3 * (nt - 1) + is] = nn;
			}
		}
		/*normals at quadrilateral vertices */
		else if (!strncmp(tictac, "NormalAtQuadrilateralVertices", 19)) {
			natureread = "NormalAtQuadrilateralVertices";
			if (!mesh->nvn) {
				printf("The field Normal need to be reading before %s", natureread);
				exit(1);
			}

			getline_number(natureread, &(mesh->extra->iq));

			mesh->extra->nq = (int *)M_calloc(4 * mesh->nq + 1, sizeof(int), "inmesh");
			assert(mesh->extra->nq);

			getline_popen_firstelemnoref(natureread, 3, tvatn);
			tvatn[0] = nq;
			tvatn[1] = is;
			tvatn[2] = nn;

			if (nq < 1 || nq > mesh->nq || is < 1 || is > 4 || nn < 1 || nn > mesh->nvn)
				disc++;
			else
				mesh->extra->nq[3 * (nq - 1) + is] = nn;

			for (k = 2; k <= mesh->extra->iq; k++) {
				getline_popen_elemnoref(natureread, 3, tvatn);
				tvatn[0] = nq;
				tvatn[1] = is;
				tvatn[2] = nn;

				if (nq < 1 || nq > mesh->nq || is < 1 || is > 4 || nn < 1 || nn > mesh->nvn)
					disc++;
				else
					mesh->extra->nq[3 * (nq - 1) + is] = nn;
			}
		}
		/*mesh tangents */
		else if (!strncmp(tictac, "Tangents", 8)) {
			natureread = "Tangents";
			getline_number(natureread, &(mesh->ntg));

			/*  allocation  */
			if (!mesh->nvn) {
				mesh->extra = (pExtra)M_calloc(1, sizeof(Extra), "zaldy1.extra");
				assert(mesh->extra);
			}

			mesh->extra->t = (float *)M_calloc(3 * mesh->ntg + 1, sizeof(float), "inmesh");
			assert(mesh->extra->t);


			for (k = 1; k <= mesh->ntg; k++) {
				n = &mesh->extra->t[3 * (k - 1) + 1];

				getline_popen_double(natureread, 3, dn);// modif FH
				n[0] = dn[0];
				n[1] = dn[1];
				n[2] = dn[2];

				d = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
				if (d > 0.0) {
					d = 1.0 / sqrt(d);
					n[0] *= d;
					n[1] *= d;
					n[2] *= d;
				}
			}
		}
		/* tangent at vertices */
		else if (!strncmp(tictac, "TangentAtVertices", 17)) {
			natureread = "TangentAtVertices";
			if (!mesh->ntg) {
				printf("The field Tangent need to be reading before %s", natureread);
				exit(1);
			}

			getline_number(natureread, &(mesh->extra->jv));
			mesh->extra->tv = (int *)M_calloc(mesh->np + 1, sizeof(int), "inmesh");
			assert(mesh->extra->tv);

			getline_popen_firstelemnoref(natureread, 2, vatn);
			nn = vatn[0];
			is = vatn[1];
			if (nn < 1 || nn > mesh->np)
				disc++;
			else
				mesh->extra->tv[nn] = is;

			for (k = 2; k <= mesh->extra->jv; k++) {
				getline_popen_elemnoref(natureread, 2, vatn);
				nn = vatn[0];
				is = vatn[1];
				if (nn < 1 || nn > mesh->np)
					disc++;
				else
					mesh->extra->tv[nn] = is;
			}
		}
		/* tangent at edge vertices */
		else if (!strncmp(tictac, "TangentAtEdgeVertices", 21)) {
			natureread = "TangentAtEdgeVertices";
			if (!mesh->ntg) {
				printf("The field Tangent need to be reading before %s", natureread);
				exit(1);
			}

			getline_number(natureread, &(mesh->extra->je));

			mesh->extra->te = (int *)M_calloc(2 * mesh->na + 1, sizeof(int), "inmesh");
			assert(mesh->extra->te);

			getline_popen_firstelemnoref(natureread, 3, tvatn);
			nt = tvatn[0];
			is = tvatn[1];
			nn = tvatn[2];
			if (nt < 1 || nt > mesh->np || is < 1 || is > 2 || nn < 1 || nn > mesh->ntg)
				disc++;
			else
				mesh->extra->te[3 * (nt - 1) + is] = is;

			for (k = 2; k <= mesh->extra->je; k++) {
				getline_popen_elemnoref(natureread, 3, tvatn);
				nt = tvatn[0];
				is = tvatn[1];
				nn = tvatn[2];
				if (nt < 1 || nt > mesh->np || is < 1 || is > 2 || nn < 1 || nn > mesh->ntg)
					disc++;
				else
					mesh->extra->te[3 * (nt - 1) + is] = is;
			}
		} else if (!strncmp(tictac, "End", 3) || !strncmp(tictac, "END", 3)) {
			if (ddebug) printf("Reading of mesh file is finished");

			break;
		}
	}

	/* check if vertices and elements found */
	if (!mesh->np) {
		fprintf(stdout, "  ## No vertex\n");
		return (-1);
	}

	mesh->ne = mesh->nt + mesh->nq + mesh->ntet + mesh->nhex;

	if (disc > 0)
		fprintf(stdout, "  ## %d entities discarded\n", disc);

	return (1);
}

/* function of lecture */

int loadScaVecTen (pMesh mesh, int numsol, int dim, int ver, int nel, int type, int size, int *typtab, int key, char *natureread) {
	pSolution sol;
	float fbuf[GmfMaxTyp]={};
	double m[6], lambda[3], eigv[3][3], vp[2][2];
	int k, i, iord, off;
	double ScaSol[1], VecSol[3], TenSol[9];

	if (numsol > type) numsol = 1;

	numsol--;
	mesh->nbb = nel;
	mesh->bbmin = 1.0e20;
	mesh->bbmax = -1.0e20;
	if (!zaldy2(mesh))
		return (0);

	sol = mesh->sol;
	sol->dim = dim;
	sol->ver = ver;

	off = 0;

	for (i = 0; i < numsol; i++) {
		switch (typtab[i]) {
		case GmfSca:
			off++;
			break;
		case GmfVec:
			off += sol->dim;
			break;
		case GmfSymMat:
			off += sol->dim * (sol->dim + 1) / 2;
			break;
		}
	}

	switch (typtab[numsol]) {
	case GmfSca:
		mesh->nfield = 1;

		for (k = 1; k <= nel; k++) {
			getline_popen_firstdouble(natureread, 1, ScaSol);
			mesh->sol[k].bb = ScaSol[0];

			if (mesh->sol[k].bb < mesh->bbmin) mesh->bbmin = mesh->sol[k].bb;

			if (mesh->sol[k].bb > mesh->bbmax) mesh->bbmax = mesh->sol[k].bb;
		}

		break;

	case GmfVec:
		if (ddebug) printf("   vector field\n");

		mesh->nfield = sol->dim;

		for (k = 1; k <= nel; k++) {
			mesh->sol[k].bb = 0.0;
			getline_popen_firstdouble(natureread, sol->dim, VecSol);

			for (i = 0; i < sol->dim; i++) {
				fbuf[off + i] = VecSol[i];
			}

			for (i = 0; i < sol->dim; i++) {
				mesh->sol[k].m[i] = fbuf[off + i];
				mesh->sol[k].bb += fbuf[off + i] * fbuf[off + i];
			}

			mesh->sol[k].bb = sqrt(mesh->sol[k].bb);
			if (mesh->sol[k].bb < mesh->bbmin) mesh->bbmin = mesh->sol[k].bb;

			if (mesh->sol[k].bb > mesh->bbmax) mesh->bbmax = mesh->sol[k].bb;
		}

		break;

	case GmfSymMat:
		if (ddebug) printf("   metric field\n");

		mesh->nfield = sol->dim * (sol->dim + 1) / 2;

		for (k = 1; k <= nel; k++) {
			getline_popen_firstdouble(natureread, sol->dim * (sol->dim + 1) / 2, TenSol);

			for (i = 0; i < sol->dim * (sol->dim + 1) / 2; i++) {
				fbuf[off + i] = TenSol[i];
			}

			if (sol->dim == 2) {
				for (i = 0; i < 3; i++) {
					mesh->sol[k].m[i] = m[i] = fbuf[off + i];
				}

				iord = eigen2(m, lambda, vp);
				if (!iord) printf("eigen2 error \n");
				mesh->sol[k].bb = min(lambda[0], lambda[1]);
				if (mesh->sol[k].bb < mesh->bbmin) mesh->bbmin = mesh->sol[k].bb;

				if (mesh->sol[k].bb > mesh->bbmax) mesh->bbmax = mesh->sol[k].bb;
			} else {
				for (i = 0; i < 6; i++) {
					mesh->sol[k].m[i] = fbuf[off + i];
				}

				mesh->sol[k].m[2] = fbuf[off + 3];
				mesh->sol[k].m[3] = fbuf[off + 2];

				for (i = 0; i < 6; i++) {
					m[i] = mesh->sol[k].m[i];
				}

				iord = eigenv(1, m, lambda, eigv);
				if (iord) {
					mesh->sol[k].bb = lambda[0];
					mesh->sol[k].bb = max(mesh->sol[k].bb, lambda[1]);
					mesh->sol[k].bb = max(mesh->sol[k].bb, lambda[2]);
					if (mesh->sol[k].bb < mesh->bbmin) mesh->bbmin = mesh->sol[k].bb;

					if (mesh->sol[k].bb > mesh->bbmax) mesh->bbmax = mesh->sol[k].bb;
				}
			}
		}

		break;
	}

	return (1);
}

/*load solution (metric) */
int loadSol_popen (pMesh mesh, char *filename, int numsol) {
	int inm=0, key, nel, size, type, typtab[GmfMaxTyp], ver=0, dim=0;
	char data[256], *res="";

	// rajout pour popen
	int NumberofSolAT;
	char *natureread;

	NumberofSolAT = 0;

	while (!feof(stdin)) {
		char *tictac;

		res = fgets(data, 256, stdin);
		if (res == NULL) printf("fgets error\n");
		tictac = strtok(data, " \n");
		if (tictac == NULL) continue;

		if (!strncmp(tictac, "MeshVersionFormatted", 20)) {
			/* read mesh format */
			natureread = "MeshVersionFormatted";

			tictac = strtok(NULL, " \n");
			printf("data= %s\n", data);
			if (tictac == NULL) {
				printf(".sol: problem in reading the %s\n", natureread);
				exit(1);
			}

			ver = atoi(tictac);


			if (debug) fprintf(stdout, ".sol: reading format %s %i \n", natureread, ver);
		}

		if (!strncmp(tictac, "Dimension", 9)) {
			/* read mesh dimension */
			natureread = "Dimension";
			tictac = strtok(NULL, " \n");
			printf("data= %s\n", data);

			if (tictac == NULL) {
				printf("problem in reading the %s\n", natureread);
				exit(1);
			}

			dim = atoi(tictac);

			/*control of the dimension*/
			if (dim != mesh->dim) {
				fprintf(stderr, "  %%%% Wrong dimension %d.\n", dim);
				GmfCloseMesh(inm);
				return (0);
			}
		}

		if (!strncmp(tictac, "SolAtVertices", 13)) {
			NumberofSolAT = NumberofSolAT + 10;
			natureread = "SolAtVertices";
			fprintf(stdout, "data= %s\n", data);
			getline_number(natureread, &(nel));
			fprintf(stdout, "nel %d, mesh->np %d  \n", nel, mesh->np);
			if (nel != mesh->np) {
				fprintf(stderr, "  %%%% Wrong number: %d Solutions discarded\n", nel - mesh->np);
				return (0);
			}

			mesh->typage = 2;
			key = GmfSolAtVertices;

			/*  type,size,typetab  */
			read_TypeSizeTyptab(natureread, &type, &size, typtab);
			printf("sol: %s; type %i; size%i;\n", natureread, type, size);

			/* Reading solutions*/
			loadScaVecTen(mesh, 1, dim, ver, nel, type, size, typtab, key, natureread);
		}

		if (mesh->dim == 2 && mesh->nt) {
			if (!strncmp(tictac, "SolAtTriangles", 14)) {
				NumberofSolAT = NumberofSolAT + 1;
				natureread = "SolAtTriangles";
				fprintf(stdout, "data= %s\n", data);
				getline_number(natureread, &(nel));

				if (nel && nel != mesh->nt) {
					fprintf(stderr, "  %%%% Wrong number %d.\n", nel);
					return (0);
				}

				mesh->typage = 1;
				key = GmfSolAtTriangles;

				/*  type,size,typetab  */
				read_TypeSizeTyptab(natureread, &type, &size, typtab);
				printf("sol: %s; type %i; size%i;\n", natureread, type, size);

				/* Reading solutions*/
				loadScaVecTen(mesh, 1, dim, ver, nel, type, size, typtab, key, natureread);
			}
		}

		if (mesh->dim == 2 && mesh->nq) {
			if (!strncmp(tictac, "SolAtQuadrilaterals", 19)) {
				NumberofSolAT = NumberofSolAT + 1;
				natureread = "SolAtQuadrilaterals";
				fprintf(stdout, "data= %s\n", data);
				getline_number(natureread, &(nel));

				if (nel && nel != mesh->nq) {
					fprintf(stderr, "  %%%% Wrong number %d.\n", nel);
					return (0);
				}

				mesh->typage = 1;
				key = GmfSolAtQuadrilaterals;

				/*  type,size,typetab  */
				read_TypeSizeTyptab(natureread, &type, &size, typtab);

				/* Reading solutions*/
				loadScaVecTen(mesh, 1, dim, ver, nel, type, size, typtab, key, natureread);
			}
		}

		if (mesh->dim == 3 && mesh->ntet) {
			if (!strncmp(tictac, "SolAtTetrahedra", 15)) {
				fprintf(stdout, "data= %s\n", data);
				NumberofSolAT = NumberofSolAT + 1;
				natureread = "SolAtTetrahedra";
				getline_number(natureread, &(nel));

				if (nel && nel != mesh->ntet) {
					fprintf(stderr, "  %%%% Wrong number %d.\n", nel);
					return (0);
				}

				mesh->typage = 1;
				key = GmfSolAtTetrahedra;

				/*  type,size,typetab  */
				read_TypeSizeTyptab(natureread, &type, &size, typtab);

				/* Reading solutions*/
				loadScaVecTen(mesh, 1, dim, ver, nel, type, size, typtab, key, natureread);
			}
		}

		if (mesh->dim == 3 && mesh->nhex) {
			if (!strncmp(tictac, "SolAtHexahedra", 14)) {
				fprintf(stdout, "data= %s\n", data);
				NumberofSolAT = NumberofSolAT + 1;
				natureread = "SolAtHexahedra";
				getline_number(natureread, &(nel));

				if (nel && nel != mesh->nhex) {
					fprintf(stderr, "  %%%% Wrong number %d.\n", nel);
					GmfCloseMesh(inm);
					return (0);
				}

				mesh->typage = 1;
				key = GmfSolAtHexahedra;

				/*  type,size,typetab  */
				read_TypeSizeTyptab(natureread, &type, &size, typtab);

				/* Reading solutions*/
				loadScaVecTen(mesh, 1, dim, ver, nel, type, size, typtab, key, natureread);
			}
		}

		if (!strncmp(tictac, "End", 3) || !strncmp(tictac, "END", 3)) {
			if (ddebug) printf("Reading of mesh file is finished");

			break;
		}
	}

	printf("NumberofSolAT %i\n", NumberofSolAT);
	;
	return (1);
}

#ifdef __cplusplus
}
#endif
