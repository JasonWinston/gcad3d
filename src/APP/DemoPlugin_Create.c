// Example create objects.
/*
 *
 * Copyright (C) 2015 CADCAM-Servies Franz Reiter (franz.reiter@cadcam.co.at)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *
-----------------------------------------------------
TODO:
  ..

-----------------------------------------------------
Modifications:
  ..

-----------------------------------------------------
*/
/*!
\file  ../APP/DemoPlugin_Create.c
\brief  demo create objects
\code
=====================================================
List_functions_start:
..
List_functions_end:
=====================================================

\endcode *//*----------------------------------------

Compile/Link/Reload is done while gCad3D is up and running !!


make -f DemoPlugin_Create.mak

*/

#ifdef _MSC_VER
#include "MS_Def1.h"
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// #include <GL/gl.h>                     // GL_TRIANGLE_FAN
#define GL_TRIANGLE_FAN  6             // unsauber ..



#ifdef _MSC_VER
// die folgenden 2 Funktionen exportieren (werden vom Main gerufen):
__declspec(dllexport) int gCad_main ();
__declspec(dllexport) int gCad_fini ();
// nachfolgende externals werden aus dem Main-Exe imported:
#define extern __declspec(dllimport)
#endif



#include "../ut/ut_geo.h"              // Point ...
#include "../ut/ut_cast.h"             // INT_PTR
#include "../ut/ut_ox_base.h"          // OGX_SET_OBJ

#include "../gui/gui__.h"

#include "../gr/ut_UI.h"               // UI_Func...
#include "../xa/xa_ui.h"                     // UID_..





static  char   cBuf[512];

char myMemspc[50000];





//=========================================================
  int gCad_fini () {
//=========================================================

  AP_User_reset ();      // close application

  return 0;
}



//=========================================================
  int gCad_main () {
//=========================================================


  printf("gCad_main aus DemoPlugin_Create\n");


  // Message ans MainWin
  TX_Print("gCad_main aus DemoPlugin_Create\n");


  // Gesamtes File loeschen
  UI_men__ ("new");

  AP_obj_2_txt (NULL, 0L, NULL, 0L);     // Init Objektindexe


  // Create permanent objects:
  cre_3 ();      // Line Circ Curv Note

  // create dynamic (visible, but not in DB):
  cre_4 ();      // symbols
  cre_5_1 ();    // (temporary) objs
  cre_5_2 ();    // Ditto
  cre_5_3 ();    // text

  cre_6 ();      // ruled surfaces
  cre_7 ();      // revolved surfaces (perm)
  cre_8 ();      // tesselated surfaces
  cre_9 ();      // planare surf; trimmed / perforated

  cre_10();      // TestDisplayfunktions (_Disp_)

  // // Redraw DispList
  // DL_Redraw ();

  UI_GR_ScalAuto (0);  // rescale all

  gCad_fini ();        // exit & reset

  return 0;

}


//=========================================================
  int cre_3 () {
//=========================================================
// create object, change obj -> text, save text, execute text.


  int    iCv1, iCv2, dbTyp;
  long   dbInd;
  Point2 pt21, pt22, pt2c, pt2a[5];
  Point  pt1, pt2, ptc, pta[5];
  Line2  ln21;
  Line   ln1;
  Circ2  ci21;
  Circ   ci1;
  GText  tx1;
  char   cbuf[80];


  // comment
  ED_add_Line ("# generated by DemoPlugin_Create");


  // create 2 2D-Points
  pt21.x=100.; pt21.y=100.;
  pt22.x=100.; pt22.y=200.;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_PT, Typ_PT2, 1, (void*)&pt21);
  UTO_sav_ost (&dbTyp, &dbInd, Typ_PT, Typ_PT2, 1, (void*)&pt22);



  // create 2 3D-Point
  pt1.x=100.; pt1.y=100.; pt1.z=100.;
  pt2.x=100.; pt2.y=200.; pt2.z=100.;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_PT, Typ_PT, 1, (void*)&pt1);
  UTO_sav_ost (&dbTyp, &dbInd, Typ_PT, Typ_PT, 1, (void*)&pt2);

  // dim following objects ..
  ED_add_Line ("DIM");


  // 2D-Line
  ln21.p1 = pt21; ln21.p2 = pt22;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_LN, Typ_LN2, 1, (void*)&ln21);


  // 3D-Line
  ln1.p1 = pt1; ln1.p2 = pt2;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_LN, Typ_LN, 1, (void*)&ln1);


  // reset dim
  ED_add_Line ("G1");


  // 2D-Circ
  ci21.pc.x=100.; ci21.pc.y=100.;
  ci21.p1.x=100.; ci21.p1.y=90.;
  ci21.p2.x=110.; ci21.p2.y=100.;
  ci21.p2 = ci21.p1;    // full circ
  ci21.rad = 10.;       // CW not possible !
  UTO_sav_ost (&dbTyp, &dbInd, Typ_CI, Typ_CI2, 1, (void*)&ci21);



  // 3D-Circ
  ci1.pc.x=100.; ci1.pc.y=100.; ci1.pc.z=100.;
  ci1.p1.x=100.; ci1.p1.y=100.; ci1.p1.z=125.;
  // ci1.p2 = ci1.p1;    // full circ
  ci1.p2.x=125.; ci1.p2.y=100.; ci1.p2.z=100.;
  ci1.vz.dx=0.;  ci1.vz.dy=1.;  ci1.vz.dz=0.;
  ci1.rad = -25.;            // pos = CCW; neg = CW
  UTO_sav_ost (&dbTyp, &dbInd, Typ_CI, Typ_CI, 1, (void*)&ci1);


  //  following -> Layer 1
  ED_add_Line ("LAY 1");



  // Text
  printf("DemoPlugin_Create: Text.\n");


  // Alfatext (does not scale)
  strcpy(cbuf, "ci1");
  tx1.pt   = ci1.pc;
  tx1.size = -1.;
  tx1.dir  = 0.;         // direction
  tx1.txt  = cbuf;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_GTXT, Typ_GTXT, 1, (void*)&tx1);


  // Graf.text (scales)
  strcpy(cbuf, "Graf.text");
  UT3D_pt_3db (&tx1.pt, 0., 100., 0.);
  tx1.size = 1.;
  tx1.dir  = 90.;         // direction
  tx1.txt  = cbuf;
  UTO_sav_ost (&dbTyp, &dbInd, Typ_GTXT, Typ_GTXT, 1, (void*)&tx1);


  // hide following, back  to layer 0
  // ED_add_Line ("DRAW OFF");
  // ED_add_Line ("LAY 0");



  // 5 points -> pta
  UT3D_pt_3db (&pta[0], 200., 0.,  0.);
  UT3D_pt_3db (&pta[1], 250., 0.,  0.);
  UT3D_pt_3db (&pta[2], 300., 50., 0.);
  UT3D_pt_3db (&pta[3], 350., 50., 0.);
  UT3D_pt_3db (&pta[4], 400., 80., 0.);


  // Polygon from 5 points
  iCv1 = UTO_sav_ost (&dbTyp, &dbInd, Typ_CVPOL, Typ_PT, 5, (void*)pta);


  // display, hilite following
  // ED_add_Line ("DRAW ON");
  // ED_add_Line ("HILI");



  // B-Spline-Curve, Degree 3  from points
  iCv2 = UTO_sav_ost (&dbTyp, &dbInd, Typ_CVBSP, Typ_PT, 5, (void*)pta);



  // convert B-Spline-Curve -> Circs




  // clean undo-tables
  UNDO_clear ();


  return 0;

}


//=========================================================
  int cre_4 () {
//=========================================================
// create dynamic objects
// Rework ("END") will delete these objects !!
// Overlaymodels (=permanent dynamic objects) not yet implemented.


  long   l1;
  Point2 pt21, pt22;
  Point  pt1,  pt2, pt3;
  Vector vc1;



  // bitmap symbols: SYM_TRI_S SYM_STAR_S SYM_TRI_B
  // att: att=0=Def, 1=sw, 2=rot, 4=bl.
  UT3D_pt_3db (&pt1, 200., 200., 50.); APT_disp_SymB (SYM_TRI_S,  0, &pt1);
  UT3D_pt_3db (&pt1, 200., 250., 50.); APT_disp_SymB (SYM_TRI_B,  1, &pt1);
  UT3D_pt_3db (&pt1, 200., 300., 50.); APT_disp_SymB (SYM_STAR_S, 2, &pt1);




  // scaled symbols: SYM_TRIANG SYM_SQUARE SYM_CROSS SYM_CROSS1
  UT3D_pt_3db (&pt1,200.,200.,0.); APT_disp_SymV1 (SYM_TRIANG, 1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,250.,0.); APT_disp_SymV1 (SYM_SQUARE, 1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,300.,0.); APT_disp_SymV1 (SYM_PLANE,  1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,350.,0.); APT_disp_SymV1 (SYM_CROSS,  1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,400.,0.); APT_disp_SymV1 (SYM_CROSS1, 1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,450.,0.); APT_disp_SymV1 (SYM_AXIS,   1, &pt1, 1.);
  UT3D_pt_3db (&pt1,200.,500.,0.); APT_disp_SymV1 (SYM_AXIS1,  1, &pt1, 1.);


  // scaled oriented symbols: SYM_ARROH (arrowheads)
  UT3D_pt_3db (&pt1, 300., 200., 0.);
  UT3D_pt_3db (&pt2, 350., 250., 0.);
  UT3D_pt_mid2pt (&pt3, &pt1, &pt2);

  APT_disp_SymV2 (SYM_ARROH, 1, &pt1, &pt2, 1.);  // head only at pt1 !
  APT_disp_SymV2 (SYM_ARROH, 1, &pt2, &pt1, 1.);  // head only at pt2 !

  APT_disp_SymV3 (SYM_ARROW, 2, &pt1, &UT3D_VECTOR_Z, 10.);  // arrow
  APT_disp_SymV3 (SYM_ARROW, 2, &pt2, &UT3D_VECTOR_Z, 10.);  // arrow
  // 3D-Arrowhead
  APT_disp_SymV3 (SYM_ARRO3H, Typ_Att_Symb, &pt3, &UT3D_VECTOR_Z, 1.);


  // 3D-Plane
  UT3D_pt_3db (&pt1, 350., 600., 100.);
  UT3D_vc_3db (&vc1,   0.,  0.75,  0.75);
  APT_disp_SymB (SYM_STAR_S,  1, &pt1);
  APT_disp_SymV3 (SYM_SQUARE, 1, &pt1, &vc1, 1.);  // arrow



  return 0;

}


//=========================================================
  int cre_5_1 () {
//=========================================================
// create dynamic objects (not stored in DB, but visible, can move, zoom ..)
// Rework ("END") will delete these objects !!

  long    id1;
  Point   pt1;
  Line    ln1;
  Circ    ci1;


  printf("cre_5_1\n");

  id1 = -1L;    // temp. elem.
  // id1 = 1;     // +1: store in dynamic area in DB


  UT3D_pt_3db (&pt1, 100.,   0.,   0.);
  GR_CrePoint (&id1, 0, &pt1);


  UT3D_pt_3db (&ln1.p1, 100.,   0.,   0.);
  UT3D_pt_3db (&ln1.p2, 100., 100.,   0.);
  ++id1; GR_CreLine (&id1, 1, &ln1);



  UT3D_pt_3db (&ci1.pc,   0.,    0.,   0.);
  UT3D_pt_3db (&ci1.p1, 100.,    0.,   0.);
  UT3D_pt_3db (&ci1.p2,   0.,    0., 100.);
  UT3D_vc_3db (&ci1.vz,   0.,   -1.,   0.);
  ci1.rad  = 100.;
  ci1.ango = UT3D_angr_ci__ (&ci1);  // MUST provide opening angle !
  id1=0; GR_CreCirc (&id1, Typ_Att_def, &ci1);
  printf(" circ %ld\n",id1);


  return 0;

}


//=========================================================
  int cre_5_2 () {
//=========================================================
// create dynamic ditto

  long    id1;
  Point   pt1, pt2, pa[4];
  Ditto   dit1;


  printf("cre_5_2\n");

  // use following polygon for ditto; save ditto-startposition (active DL-posi)
  dit1.ind = GL_Get_DLind();


  // create attrib 
  // (AttNr, col(2=r,3=g,4=b),typ(0=voll,1=-.,2=- -, 3=--),thick(1-6))
  DL_InitAttRec (20,    4, 2, 3);  // att 20 = blue, strichl, thick3



  id1 = -1L;    // temp. elem.

  // polygon
  UT3D_pt_3db (&pa[0], 100.,  200.,   0.);
  UT3D_pt_3db (&pa[1], 100.,  250.,   0.);
  UT3D_pt_3db (&pa[2], 100.,  250., 100.);
  UT3D_pt_3db (&pa[3], 100.,  200., 100.);
  GR_CrePoly (&id1, 20, 4, &pa);

  DL_hide__ (GL_GetActInd(), OFF);         // hide last created Obj



  UT3D_pt_3db (&dit1.po, 100., 200., 0.);      // origin (rotate-pos)
  dit1.siz = GL_Get_DLind() - dit1.ind;        // save size of ditto
  UT3D_pt_3db (&pt1, 100.,   400.,   0.);      // new dittopos

  // ditto (pos, rotAng, mirror, ditto)
  // mirror: no=' ', 'X'=X-Z-plane, 'Y'=Y-Z-plane
  ++id1; GR_CreDitto2 (&id1, &pt1,  0., ' ', &dit1);
  ++id1; GR_CreDitto2 (&id1, &pt1, 30., 'X', &dit1);
  ++id1; GR_CreDitto2 (&id1, &pt1, 60., 'X', &dit1);
  ++id1; GR_CreDitto2 (&id1, &pt1, 90., ' ', &dit1);

  return 0;

}


//=========================================================
  int cre_5_3 () {
//=========================================================
// create dynamic text

  long    id1;
  Point   pt1;


  printf("cre_5_3\n");


  id1 = -1L;    // temp. elem.


  // bitmap text: (ID, att, pt, text)
  UT3D_pt_3db (&pt1, 200.,   0.,   0.);
  GR_CreTxtA (&id1, Typ_Att_Symb, &pt1, "abc");


  // scaled rotated text: (ID, att, pt, scale, dir, text)
  UT3D_pt_3db (&pt1, 200.,  50.,   0.);
  GR_CreTxtG (&id1, 1, &pt1, 15., 90., "--->>>");


  return 0;

}


//=========================================================
  int cre_6 () {
//=========================================================
// ruled surfaces ..

  long   id1;
  Point  pt1,  pt2, pa[9];
  Line   ln1, ln2;
  Vector v1;
  Circ   ci1;
  ObjGX  os, oa[2];


  printf("cre_6\n");



  // create Lineobj
  UT3D_pt_3db (&ln1.p1, 300.,  0.,   0.);
  UT3D_pt_3db (&ln1.p2, 350.,  0.,   0.);
  OGX_SET_OBJ (&oa[0], Typ_LN, Typ_LN, 1, &ln1);

  // create pointobj
  UT3D_pt_3db (&pt1, 300.,  0.,   100.);
  OGX_SET_OBJ (&oa[1], Typ_PT, Typ_PT, 1, &pt1);

  // create ruled surf from line + point
  OGX_SET_OBJ (&os, Typ_SURRU, Typ_ObjGX, 2, oa);

  // draw ruled surf
  TSU_DrawSurT_ (&os, Typ_Att_Fac1, 0L);



  // create ln 1
  UT3D_pt_3db (&ln1.p1, 300.,  100.,   0.);
  UT3D_pt_3db (&ln1.p2, 350.,  100.,   0.);
  OGX_SET_OBJ (&oa[0], Typ_LN, Typ_LN, 1, &ln1);

  // create ln 2
  UT3D_pt_3db (&ln2.p1, 320.,  120.,   100.);
  UT3D_pt_3db (&ln2.p2, 350.,  100.,   100.);
  OGX_SET_OBJ (&oa[1], Typ_LN, Typ_LN, 1, &ln2);

  // create ruled surf from 2 lines
  OGX_SET_OBJ (&os, Typ_SURRU, Typ_ObjGX, 2, oa);
    // UTO_dump__ (&os, "SURRU ln+ln:");
    // UTO_dump_s_ (&os, "SURRU ln+ln:");

  // display
  TSU_DrawSurT_ (&os, Typ_Att_Fac1, 0L);




  UT3D_pt_3db (&ln1.p1, 300.,  200.,   0.);
  UT3D_pt_3db (&ln1.p2, 350.,  200.,   0.);
  // ruled obj # 1 = ln
  OGX_SET_OBJ (&oa[0], Typ_LN, Typ_LN, 1, &ln1);


  UT3D_pt_3db (&pt1, 350.,  200.,   100.);
  UT3D_pt_3db (&pt2, 300.,  200.,   100.);
  // Z-vector of active construction-plane
  AP_Get_ConstPl_vz (&v1);

  // Circ from center, startpoint, axis, opening angle
  UT3D_ci_ptptvcangr (&ci1, &pt1, &pt2, &v1, UT_RADIANS(-120.));
    UT3D_stru_dump (Typ_CI, &ci1, "ci1");
  OGX_SET_OBJ (&oa[1], Typ_CI, Typ_CI, 1, &ci1);

  // ruled obj from line & circ
  OGX_SET_OBJ (&os, Typ_SURRU, Typ_ObjGX, 2, oa);
  TSU_DrawSurT_ (&os, Typ_Att_Fac1, 0L);





  UT3D_pt_3db (&pt1, 450.,  0.,  75.);
  UT3D_pt_3db (&pt2, 450.,  0.,   0.);
  id1 = 1;
  // cylinder (ID, att, cen1, cen2, rad1, rad2)
  GR_CreCyl (&id1, Typ_Att_Fac1, &pt1, &pt2, 15., 35.);




  id1 = 1;
  UT3D_pt_3db (&pt1, 450.,  0.,   0.);
  // disc (ID, att, cen, vector, inner_rad, outer_rad)
  GR_CreDisk (&id1, Typ_Att_Fac1, &pt1, &UT3D_VECTOR_Z, -35., -50.0);




  // triangle-fan (ID, att, startpt, nr_of_points, points)
  id1 = 1;
  UT3D_pt_3db (&pa[0], 350.,  300.,   0.);
  UT3D_pt_3db (&pa[1], 350.,  350.,   0.);
  UT3D_pt_3db (&pa[2], 350.,  350.,  75.);
  UT3D_pt_3db (&pa[3], 350.,  300.,  75.);
  GR_CreTriaFan (&id1, Typ_Att_Fac1, pa, 3, &pa[1]);



  // triangle-strip (ID, att, nr_of_points_dir1, nr_of_points_dir2, points)
  UT3D_pt_3db (&pa[0], 350.,  400.,   0.);
  UT3D_pt_3db (&pa[1], 350.,  450.,   0.);
  UT3D_pt_3db (&pa[2], 350.,  500.,   0.);

  UT3D_pt_3db (&pa[3], 348.,  400.,  25.);
  UT3D_pt_3db (&pa[4], 346.,  450.,  25.);
  UT3D_pt_3db (&pa[5], 348.,  500.,  25.);

  UT3D_pt_3db (&pa[6], 350.,  400.,  50.);
  UT3D_pt_3db (&pa[7], 350.,  450.,  50.);
  UT3D_pt_3db (&pa[8], 350.,  500.,  50.);

  GR_CreTriaStrip (&id1, Typ_Att_Fac1, 3, 3, pa);


  return 0;

}


//=========================================================
  int cre_7 () {
//=========================================================
// revolved surfaces (perm)

  int    typ1, typ2, dbTyp;
  long   id1, id2, dbInd;
  Point  cvp[]={500.,100.,0.,
                520.,125.,0.,
                550.,150.,0.,
                520.,175.,0.,
                500.,200.,0.};
  Line     ln1, ln2;
  SurRev   srv;
  Memspc   memSeg1;
  CurvBSpl cv1;
  ObjGX    os, ocv;


  printf("cre_7 \n");


  // create Centerline
  UT3D_pt_3db (&ln1.p1, 450.,  100.,   0.);
  UT3D_pt_3db (&ln1.p2, 450.,  150.,   0.);
  // id1 = DB_StoreLine (DB_QueryNxtFree(Typ_LN, 1), &ln1);
  // AP_obj_2_txt_query (&typ1, &id1);           // query index
  UTO_sav_ost (&dbTyp, &id1, Typ_LN, Typ_LN, 1, (void*)&ln1);


  // create contour
  UME_init (&memSeg1, myMemspc, sizeof(myMemspc));  // init memoryseg (tempspc)
  //           (cvBsp, &memSeg1, pTab, ptNr, deg);
  bspl_bsp_ptn (&cv1,  &memSeg1, cvp,     5,   3);  // make BSP-curve from pTab
  // OGX_SET_OBJ (&ocv, Typ_CVBSP, Typ_CVBSP, 1, &cv1);
  // id2 = DB_StoreCurv (DB_QueryNxtFree(Typ_CV, 1), &ocv, 0);
  // AP_obj_2_txt_query (&typ2, &id2);           // query index
  UTO_sav_ost (&dbTyp, &id2, Typ_CVBSP, Typ_CVBSP, 1, (void*)&cv1);


  // RevSur
  srv.indCen = id1;              // Ind of Centerline (Typ = Typ_LN)
  srv.typCen = Typ_LN;           // typ of Centerline
  srv.indCov = id2;              // Ind of contourelement
  srv.typCov = Typ_CV;           // typ of contourelement
  srv.ang1   = UT_RADIANS(300.); // starting angle
  srv.ang2   = UT_RADIANS(360.); // ending angle
  srv.v0     = 0.;               // ending par.
  srv.v1     = 1.;               // ending par.


  UTO_sav_ost (&dbTyp, &dbInd, Typ_SURRV, Typ_SURRV, 1, (void*)&srv);
  // OGX_SET_OBJ (&os, Typ_SURRV, Typ_SURRV, 1, &srv);
  // TSU_DrawSurT_ (&os, Typ_Att_Fac1, 0L);
  


  return 0;

}


//=========================================================
  int cre_8 () {
//=========================================================
// create tesselated surface manually
// Surf = 1-n PlanarPatches
//            Planar patch = 1-n contours (and vector)
//                               Contour = ipoints (closed, tesselated)

  long  il;
  ObjGX gCont[10], gPat[2], gSur;

  Point pp1[]={600., 0., 0., 650., 0., 0.,
               650.,20., 0., 600.,20., 0., 600., 0., 0.,};
  Point pp2[]={600.,20., 0., 650.,20., 0.,
               650.,40., 0., 600.,40., 0., 600.,20., 0.,};
  Point pp3[]={600.,40., 0., 650.,40., 0.,
               650.,40.,40., 600.,40.,40., 600.,40., 0.,};


  //----------------------------------------------------------------
  // Create sur
  gSur.typ  = Typ_GL_Sur;
  gSur.form = Typ_ObjGX;
  gSur.siz  = 1;
  gSur.data = gPat;


  // Create 1. Patch
  gPat[0].typ  = Typ_GL_PP;
  gPat[0].form = Typ_ObjGX;
  gPat[0].siz  = 0;
  gPat[0].data = &gCont[0];


  //----------------------------------------------------------------
  // add  vector to 1. patch
  gCont[0].typ  = Typ_VC;
  gCont[0].form = Typ_VC;
  gCont[0].siz  = 1;
  gCont[0].data = (Vector*)&UT3D_VECTOR_Z;

  gPat[0].siz  = 1;


  //----------------------------------------------------------------
  // add 1. contour to 1. patch
  gCont[1].typ  = Typ_PT;
  gCont[1].form = Typ_PT;
  gCont[1].siz  = 5;
  gCont[1].data = pp1;
  gCont[1].aux  = GL_TRIANGLE_FAN;

  gPat[0].siz  = 2;


  //----------------------------------------------------------------
  // add 2. contour to 1. patch
  gCont[2].typ  = Typ_PT;
  gCont[2].form = Typ_PT;
  gCont[2].siz  = 5;
  gCont[2].data = pp2;
  gCont[2].aux  = GL_TRIANGLE_FAN;

  gPat[0].siz  = 3;


  //================================================================
  // add 2. patch to surf
  gPat[1].typ  = Typ_GL_PP;
  gPat[1].form = Typ_ObjGX;
  gPat[1].siz  = 0; // 2
  gPat[1].data = &gCont[3];

  gSur.siz  = 2;


  //----------------------------------------------------------------
  // add vector to 2. patch
  gCont[3].typ  = Typ_VC;
  gCont[3].form = Typ_VC;
  gCont[3].siz  = 1;
  gCont[3].data = (Vector*)&UT3D_VECTOR_IY;

  gPat[1].siz  = 1;


  //----------------------------------------------------------------
  // add 1. contour to 2. patch
  gCont[4].typ  = Typ_PT;
  gCont[4].form = Typ_PT;
  gCont[4].siz  = 5;
  gCont[4].data = pp3;
  gCont[4].aux  = GL_TRIANGLE_FAN;

  gPat[1].siz  = 2;


  //----------------------------------------------------------------
  // display
  il = DL_StoreObj (Typ_SUR, 20L, Typ_Att_Fac1);  // identifier 20
  // UTO_dump_s_ (&gSur, "sur-tess:");
  // UTO_dump__ (&gSur, "sur-tess:");
  GL_DrawSur (&il, Typ_Att_Fac1, &gSur);


  return 0;

}



//=========================================================
  int cre_9 () {
//=========================================================
// planare surf; trimmed / perforated

  Point pp1[]={600.,100., 0., 650.,100., 0.,
               650.,200., 0., 600.,200., 0., 600.,100., 0.};

  Point pp2[]={625.,125., 0., 625.,175., 0.};

  int      irc;
  long     id1, id2, id3, ids;
  Vector   v1;
  Circ     ci1;
  CurvPoly plg1;
  ObjGX    os, oa[4], otmp;
  Memspc   memSeg1;


  printf("cre_9 \n");

  // Z-vector of active construction-plane
  AP_Get_ConstPl_vz (&v1);


  // save Polygon pp1
  UME_init (&memSeg1, myMemspc, sizeof(myMemspc));  // init memoryseg (tempspc)
  UT3D_plg_pta (&plg1, pp1, 5, &memSeg1);           // PolgonCurve from pt-tab
  OGX_SET_OBJ (&otmp, Typ_CVPOL, Typ_CVPOL, 1, &plg1);
    // UT3D_stru_dump(Typ_CVPOL, otmp.data, "plg1:");
  id1 = DB_StoreCurv (DB_QueryNxtFree(Typ_CV, 1), &otmp, 0);  // save in DB



  // save holes
  UT3D_ci_ptvcr (&ci1, &pp2[0], &v1, 20.);
  OGX_SET_OBJ (&otmp, Typ_CI, Typ_CI, 1, &ci1);
  id2 = DB_StoreCirc (DB_QueryNxtFree(Typ_CI, 1), &ci1);

  UT3D_ci_ptvcr (&ci1, &pp2[1], &v1, 20.);
  OGX_SET_OBJ (&otmp, Typ_CI, Typ_CI, 1, &ci1);
  id3 = DB_StoreCirc (DB_QueryNxtFree(Typ_CI, 1), &ci1);


  // 1.obj: define typ of supporting surface (planar)
  OGX_SET_OBJ (&oa[0], Typ_Typ, Typ_Int4, 1, (void*)Typ_SURPLN);

  // 2.obj: boundary; 3,4: holes
  OGX_SET_INDEX (&oa[1], Typ_CV, id1);
  OGX_SET_INDEX (&oa[2], Typ_CI, id2);
  OGX_SET_INDEX (&oa[3], Typ_CI, id3);

  // all -> container
  OGX_SET_OBJ (&os, Typ_SUR, Typ_ObjGX, 4, &oa);
    UTO_dump__ (&os, "os=");

  // draw
  ids = DB_QueryNxtFree(Typ_SUR, 1);
  irc = DB_StoreSur (&ids, &os);

  TSU_DrawSurT_ (&os, Typ_Att_Fac1, ids);
  
  return 0;

}


//=========================================================
  int cre_10 () {
//=========================================================
// TestDisplayfunktions (_Disp_)


  int    i1;
  Point  pt1;
  Vector v1;
  Point  pp1[]={600.,300., 0., 650.,300., 0.,
                650.,400., 0., 600.,400., 0., 600.,300., 0.};


  // display points with symbols
  GR_Disp_pTab (5, pp1, SYM_TRI_S, 2);


  // display numbers at points
  for(i1=0; i1<4; ++i1) GR_Disp_txi (&pp1[i1], i1, 0);


  // display curve
  GR_Disp_cv (pp1, 5, 2);

  
  // display vector
  UT3D_pt_mid2pt (&pt1, &pp1[0], &pp1[2]);
  AP_Get_ConstPl_vz (&v1);
  GR_Disp_vc (&v1, &pt1, 2, 0); // 0="normiert", 1=wahre Groesse


  // display surf - planar - unperforated
  GR_Disp_spu (5, pp1, Typ_Att_Fac1);


  return 0;

}


//======================== EOF ======================
