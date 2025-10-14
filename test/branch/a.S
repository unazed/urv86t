
a.out:     file format elf32-littleriscv


Disassembly of section .text:

000100b4 <exit>:
   100b4:	ff010113          	addi	sp,sp,-16
   100b8:	00000593          	addi	a1,zero,0
   100bc:	00812423          	sw	s0,8(sp)
   100c0:	00112623          	sw	ra,12(sp)
   100c4:	00050413          	addi	s0,a0,0
   100c8:	575000ef          	jal	ra,10e3c <__call_exitprocs>
   100cc:	d501a783          	lw	a5,-688(gp) # 138f0 <__stdio_exit_handler>
   100d0:	00078463          	beq	a5,zero,100d8 <exit+0x24>
   100d4:	000780e7          	jalr	ra,0(a5)
   100d8:	00040513          	addi	a0,s0,0
   100dc:	130020ef          	jal	ra,1220c <_exit>

000100e0 <register_fini>:
   100e0:	00000793          	addi	a5,zero,0
   100e4:	00078863          	beq	a5,zero,100f4 <register_fini+0x14>
   100e8:	00001517          	auipc	a0,0x1
   100ec:	b0850513          	addi	a0,a0,-1272 # 10bf0 <__libc_fini_array>
   100f0:	1040006f          	jal	zero,101f4 <atexit>
   100f4:	00008067          	jalr	zero,0(ra)

000100f8 <_start>:
   100f8:	00004197          	auipc	gp,0x4
   100fc:	aa818193          	addi	gp,gp,-1368 # 13ba0 <__global_pointer$>
   10100:	d4c18513          	addi	a0,gp,-692 # 138ec <completed.1>
   10104:	09418613          	addi	a2,gp,148 # 13c34 <__BSS_END__>
   10108:	40a60633          	sub	a2,a2,a0
   1010c:	00000593          	addi	a1,zero,0
   10110:	36d000ef          	jal	ra,10c7c <memset>
   10114:	00001517          	auipc	a0,0x1
   10118:	adc50513          	addi	a0,a0,-1316 # 10bf0 <__libc_fini_array>
   1011c:	0d8000ef          	jal	ra,101f4 <atexit>
   10120:	23d000ef          	jal	ra,10b5c <__libc_init_array>
   10124:	00012503          	lw	a0,0(sp)
   10128:	00410593          	addi	a1,sp,4
   1012c:	00000613          	addi	a2,zero,0
   10130:	074000ef          	jal	ra,101a4 <main>
   10134:	f81ff06f          	jal	zero,100b4 <exit>

00010138 <__do_global_dtors_aux>:
   10138:	d4c1c783          	lbu	a5,-692(gp) # 138ec <completed.1>
   1013c:	04079263          	bne	a5,zero,10180 <__do_global_dtors_aux+0x48>
   10140:	00000793          	addi	a5,zero,0
   10144:	02078863          	beq	a5,zero,10174 <__do_global_dtors_aux+0x3c>
   10148:	ff010113          	addi	sp,sp,-16
   1014c:	00002517          	auipc	a0,0x2
   10150:	24050513          	addi	a0,a0,576 # 1238c <__EH_FRAME_BEGIN__>
   10154:	00112623          	sw	ra,12(sp)
   10158:	00000097          	auipc	ra,0x0
   1015c:	000000e7          	jalr	ra,0(zero) # 0 <exit-0x100b4>
   10160:	00c12083          	lw	ra,12(sp)
   10164:	00100793          	addi	a5,zero,1
   10168:	d4f18623          	sb	a5,-692(gp) # 138ec <completed.1>
   1016c:	01010113          	addi	sp,sp,16
   10170:	00008067          	jalr	zero,0(ra) # 10158 <__do_global_dtors_aux+0x20>
   10174:	00100793          	addi	a5,zero,1
   10178:	d4f18623          	sb	a5,-692(gp) # 138ec <completed.1>
   1017c:	00008067          	jalr	zero,0(ra)
   10180:	00008067          	jalr	zero,0(ra)

00010184 <frame_dummy>:
   10184:	00000793          	addi	a5,zero,0
   10188:	00078c63          	beq	a5,zero,101a0 <frame_dummy+0x1c>
   1018c:	d8c18593          	addi	a1,gp,-628 # 1392c <object.0>
   10190:	00002517          	auipc	a0,0x2
   10194:	1fc50513          	addi	a0,a0,508 # 1238c <__EH_FRAME_BEGIN__>
   10198:	00000317          	auipc	t1,0x0
   1019c:	00000067          	jalr	zero,0(zero) # 0 <exit-0x100b4>
   101a0:	00008067          	jalr	zero,0(ra)

000101a4 <main>:
   101a4:	fe010113          	addi	sp,sp,-32
   101a8:	00112e23          	sw	ra,28(sp)
   101ac:	00812c23          	sw	s0,24(sp)
   101b0:	02010413          	addi	s0,sp,32
   101b4:	00100793          	addi	a5,zero,1
   101b8:	fef42623          	sw	a5,-20(s0)
   101bc:	fec42703          	lw	a4,-20(s0)
   101c0:	00200793          	addi	a5,zero,2
   101c4:	00e7d863          	bge	a5,a4,101d4 <main+0x30>
   101c8:	00300793          	addi	a5,zero,3
   101cc:	fef42623          	sw	a5,-20(s0)
   101d0:	00c0006f          	jal	zero,101dc <main+0x38>
   101d4:	00400793          	addi	a5,zero,4
   101d8:	fef42623          	sw	a5,-20(s0)
   101dc:	00000793          	addi	a5,zero,0
   101e0:	00078513          	addi	a0,a5,0
   101e4:	01c12083          	lw	ra,28(sp)
   101e8:	01812403          	lw	s0,24(sp)
   101ec:	02010113          	addi	sp,sp,32
   101f0:	00008067          	jalr	zero,0(ra)

000101f4 <atexit>:
   101f4:	00050593          	addi	a1,a0,0
   101f8:	00000693          	addi	a3,zero,0
   101fc:	00000613          	addi	a2,zero,0
   10200:	00000513          	addi	a0,zero,0
   10204:	3550006f          	jal	zero,10d58 <__register_exitproc>

00010208 <stdio_exit_handler>:
   10208:	00003617          	auipc	a2,0x3
   1020c:	19860613          	addi	a2,a2,408 # 133a0 <__sglue>
   10210:	00002597          	auipc	a1,0x2
   10214:	9c858593          	addi	a1,a1,-1592 # 11bd8 <_fclose_r>
   10218:	00003517          	auipc	a0,0x3
   1021c:	19850513          	addi	a0,a0,408 # 133b0 <_impure_data>
   10220:	4680006f          	jal	zero,10688 <_fwalk_sglue>

00010224 <cleanup_stdio>:
   10224:	00452583          	lw	a1,4(a0)
   10228:	ff010113          	addi	sp,sp,-16
   1022c:	00812423          	sw	s0,8(sp)
   10230:	00112623          	sw	ra,12(sp)
   10234:	da418793          	addi	a5,gp,-604 # 13944 <__sf>
   10238:	00050413          	addi	s0,a0,0
   1023c:	00f58463          	beq	a1,a5,10244 <cleanup_stdio+0x20>
   10240:	199010ef          	jal	ra,11bd8 <_fclose_r>
   10244:	00842583          	lw	a1,8(s0)
   10248:	e0c18793          	addi	a5,gp,-500 # 139ac <__sf+0x68>
   1024c:	00f58663          	beq	a1,a5,10258 <cleanup_stdio+0x34>
   10250:	00040513          	addi	a0,s0,0
   10254:	185010ef          	jal	ra,11bd8 <_fclose_r>
   10258:	00c42583          	lw	a1,12(s0)
   1025c:	e7418793          	addi	a5,gp,-396 # 13a14 <__sf+0xd0>
   10260:	00f58c63          	beq	a1,a5,10278 <cleanup_stdio+0x54>
   10264:	00040513          	addi	a0,s0,0
   10268:	00812403          	lw	s0,8(sp)
   1026c:	00c12083          	lw	ra,12(sp)
   10270:	01010113          	addi	sp,sp,16
   10274:	1650106f          	jal	zero,11bd8 <_fclose_r>
   10278:	00c12083          	lw	ra,12(sp)
   1027c:	00812403          	lw	s0,8(sp)
   10280:	01010113          	addi	sp,sp,16
   10284:	00008067          	jalr	zero,0(ra)

00010288 <__fp_lock>:
   10288:	0645a783          	lw	a5,100(a1)
   1028c:	0017f793          	andi	a5,a5,1
   10290:	00079863          	bne	a5,zero,102a0 <__fp_lock+0x18>
   10294:	00c5d783          	lhu	a5,12(a1)
   10298:	2007f793          	andi	a5,a5,512
   1029c:	00078663          	beq	a5,zero,102a8 <__fp_lock+0x20>
   102a0:	00000513          	addi	a0,zero,0
   102a4:	00008067          	jalr	zero,0(ra)
   102a8:	0585a503          	lw	a0,88(a1)
   102ac:	ff010113          	addi	sp,sp,-16
   102b0:	00112623          	sw	ra,12(sp)
   102b4:	1ad000ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   102b8:	00c12083          	lw	ra,12(sp)
   102bc:	00000513          	addi	a0,zero,0
   102c0:	01010113          	addi	sp,sp,16
   102c4:	00008067          	jalr	zero,0(ra)

000102c8 <__fp_unlock>:
   102c8:	0645a783          	lw	a5,100(a1)
   102cc:	0017f793          	andi	a5,a5,1
   102d0:	00079863          	bne	a5,zero,102e0 <__fp_unlock+0x18>
   102d4:	00c5d783          	lhu	a5,12(a1)
   102d8:	2007f793          	andi	a5,a5,512
   102dc:	00078663          	beq	a5,zero,102e8 <__fp_unlock+0x20>
   102e0:	00000513          	addi	a0,zero,0
   102e4:	00008067          	jalr	zero,0(ra)
   102e8:	0585a503          	lw	a0,88(a1)
   102ec:	ff010113          	addi	sp,sp,-16
   102f0:	00112623          	sw	ra,12(sp)
   102f4:	185000ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   102f8:	00c12083          	lw	ra,12(sp)
   102fc:	00000513          	addi	a0,zero,0
   10300:	01010113          	addi	sp,sp,16
   10304:	00008067          	jalr	zero,0(ra)

00010308 <global_stdio_init.part.0>:
   10308:	fe010113          	addi	sp,sp,-32
   1030c:	00112e23          	sw	ra,28(sp)
   10310:	00812c23          	sw	s0,24(sp)
   10314:	00912a23          	sw	s1,20(sp)
   10318:	da418413          	addi	s0,gp,-604 # 13944 <__sf>
   1031c:	01212823          	sw	s2,16(sp)
   10320:	01312623          	sw	s3,12(sp)
   10324:	01412423          	sw	s4,8(sp)
   10328:	00000717          	auipc	a4,0x0
   1032c:	ee070713          	addi	a4,a4,-288 # 10208 <stdio_exit_handler>
   10330:	00400793          	addi	a5,zero,4
   10334:	00800613          	addi	a2,zero,8
   10338:	00000593          	addi	a1,zero,0
   1033c:	e0018513          	addi	a0,gp,-512 # 139a0 <__sf+0x5c>
   10340:	d4e1a823          	sw	a4,-688(gp) # 138f0 <__stdio_exit_handler>
   10344:	00f42623          	sw	a5,12(s0)
   10348:	00042023          	sw	zero,0(s0)
   1034c:	00042223          	sw	zero,4(s0)
   10350:	00042423          	sw	zero,8(s0)
   10354:	06042223          	sw	zero,100(s0)
   10358:	00042823          	sw	zero,16(s0)
   1035c:	00042a23          	sw	zero,20(s0)
   10360:	00042c23          	sw	zero,24(s0)
   10364:	119000ef          	jal	ra,10c7c <memset>
   10368:	00000a17          	auipc	s4,0x0
   1036c:	3d4a0a13          	addi	s4,s4,980 # 1073c <__sread>
   10370:	00000997          	auipc	s3,0x0
   10374:	43098993          	addi	s3,s3,1072 # 107a0 <__swrite>
   10378:	00000917          	auipc	s2,0x0
   1037c:	4b090913          	addi	s2,s2,1200 # 10828 <__sseek>
   10380:	00000497          	auipc	s1,0x0
   10384:	50c48493          	addi	s1,s1,1292 # 1088c <__sclose>
   10388:	dfc18513          	addi	a0,gp,-516 # 1399c <__sf+0x58>
   1038c:	03442023          	sw	s4,32(s0)
   10390:	03342223          	sw	s3,36(s0)
   10394:	03242423          	sw	s2,40(s0)
   10398:	02942623          	sw	s1,44(s0)
   1039c:	00842e23          	sw	s0,28(s0)
   103a0:	0b1000ef          	jal	ra,10c50 <__retarget_lock_init_recursive>
   103a4:	000107b7          	lui	a5,0x10
   103a8:	00978793          	addi	a5,a5,9 # 10009 <exit-0xab>
   103ac:	00800613          	addi	a2,zero,8
   103b0:	00000593          	addi	a1,zero,0
   103b4:	e6818513          	addi	a0,gp,-408 # 13a08 <__sf+0xc4>
   103b8:	06f42a23          	sw	a5,116(s0)
   103bc:	06042423          	sw	zero,104(s0)
   103c0:	06042623          	sw	zero,108(s0)
   103c4:	06042823          	sw	zero,112(s0)
   103c8:	0c042623          	sw	zero,204(s0)
   103cc:	06042c23          	sw	zero,120(s0)
   103d0:	06042e23          	sw	zero,124(s0)
   103d4:	08042023          	sw	zero,128(s0)
   103d8:	0a5000ef          	jal	ra,10c7c <memset>
   103dc:	e0c18793          	addi	a5,gp,-500 # 139ac <__sf+0x68>
   103e0:	e6418513          	addi	a0,gp,-412 # 13a04 <__sf+0xc0>
   103e4:	09442423          	sw	s4,136(s0)
   103e8:	09342623          	sw	s3,140(s0)
   103ec:	09242823          	sw	s2,144(s0)
   103f0:	08942a23          	sw	s1,148(s0)
   103f4:	08f42223          	sw	a5,132(s0)
   103f8:	059000ef          	jal	ra,10c50 <__retarget_lock_init_recursive>
   103fc:	000207b7          	lui	a5,0x20
   10400:	01278793          	addi	a5,a5,18 # 20012 <__BSS_END__+0xc3de>
   10404:	00800613          	addi	a2,zero,8
   10408:	00000593          	addi	a1,zero,0
   1040c:	ed018513          	addi	a0,gp,-304 # 13a70 <__sf+0x12c>
   10410:	0cf42e23          	sw	a5,220(s0)
   10414:	0c042823          	sw	zero,208(s0)
   10418:	0c042a23          	sw	zero,212(s0)
   1041c:	0c042c23          	sw	zero,216(s0)
   10420:	12042a23          	sw	zero,308(s0)
   10424:	0e042023          	sw	zero,224(s0)
   10428:	0e042223          	sw	zero,228(s0)
   1042c:	0e042423          	sw	zero,232(s0)
   10430:	04d000ef          	jal	ra,10c7c <memset>
   10434:	e7418793          	addi	a5,gp,-396 # 13a14 <__sf+0xd0>
   10438:	0f442823          	sw	s4,240(s0)
   1043c:	0f342a23          	sw	s3,244(s0)
   10440:	0f242c23          	sw	s2,248(s0)
   10444:	0e942e23          	sw	s1,252(s0)
   10448:	0ef42623          	sw	a5,236(s0)
   1044c:	01812403          	lw	s0,24(sp)
   10450:	01c12083          	lw	ra,28(sp)
   10454:	01412483          	lw	s1,20(sp)
   10458:	01012903          	lw	s2,16(sp)
   1045c:	00c12983          	lw	s3,12(sp)
   10460:	00812a03          	lw	s4,8(sp)
   10464:	ecc18513          	addi	a0,gp,-308 # 13a6c <__sf+0x128>
   10468:	02010113          	addi	sp,sp,32
   1046c:	7e40006f          	jal	zero,10c50 <__retarget_lock_init_recursive>

00010470 <__sfp>:
   10470:	fe010113          	addi	sp,sp,-32
   10474:	01312623          	sw	s3,12(sp)
   10478:	00050993          	addi	s3,a0,0
   1047c:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   10480:	00112e23          	sw	ra,28(sp)
   10484:	00812c23          	sw	s0,24(sp)
   10488:	00912a23          	sw	s1,20(sp)
   1048c:	01212823          	sw	s2,16(sp)
   10490:	7d0000ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   10494:	d501a783          	lw	a5,-688(gp) # 138f0 <__stdio_exit_handler>
   10498:	10078063          	beq	a5,zero,10598 <__sfp+0x128>
   1049c:	00003917          	auipc	s2,0x3
   104a0:	f0490913          	addi	s2,s2,-252 # 133a0 <__sglue>
   104a4:	fff00493          	addi	s1,zero,-1
   104a8:	00492783          	lw	a5,4(s2)
   104ac:	00892403          	lw	s0,8(s2)
   104b0:	fff78793          	addi	a5,a5,-1
   104b4:	0007d863          	bge	a5,zero,104c4 <__sfp+0x54>
   104b8:	0900006f          	jal	zero,10548 <__sfp+0xd8>
   104bc:	06840413          	addi	s0,s0,104
   104c0:	08978463          	beq	a5,s1,10548 <__sfp+0xd8>
   104c4:	00c41703          	lh	a4,12(s0)
   104c8:	fff78793          	addi	a5,a5,-1
   104cc:	fe0718e3          	bne	a4,zero,104bc <__sfp+0x4c>
   104d0:	ffff07b7          	lui	a5,0xffff0
   104d4:	00178793          	addi	a5,a5,1 # ffff0001 <__BSS_END__+0xfffdc3cd>
   104d8:	00f42623          	sw	a5,12(s0)
   104dc:	05840513          	addi	a0,s0,88
   104e0:	06042223          	sw	zero,100(s0)
   104e4:	76c000ef          	jal	ra,10c50 <__retarget_lock_init_recursive>
   104e8:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   104ec:	78c000ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   104f0:	05c40513          	addi	a0,s0,92
   104f4:	00042023          	sw	zero,0(s0)
   104f8:	00042423          	sw	zero,8(s0)
   104fc:	00042223          	sw	zero,4(s0)
   10500:	00042823          	sw	zero,16(s0)
   10504:	00042a23          	sw	zero,20(s0)
   10508:	00042c23          	sw	zero,24(s0)
   1050c:	00800613          	addi	a2,zero,8
   10510:	00000593          	addi	a1,zero,0
   10514:	768000ef          	jal	ra,10c7c <memset>
   10518:	02042823          	sw	zero,48(s0)
   1051c:	02042a23          	sw	zero,52(s0)
   10520:	04042223          	sw	zero,68(s0)
   10524:	04042423          	sw	zero,72(s0)
   10528:	01c12083          	lw	ra,28(sp)
   1052c:	00040513          	addi	a0,s0,0
   10530:	01812403          	lw	s0,24(sp)
   10534:	01412483          	lw	s1,20(sp)
   10538:	01012903          	lw	s2,16(sp)
   1053c:	00c12983          	lw	s3,12(sp)
   10540:	02010113          	addi	sp,sp,32
   10544:	00008067          	jalr	zero,0(ra)
   10548:	00092403          	lw	s0,0(s2)
   1054c:	00040663          	beq	s0,zero,10558 <__sfp+0xe8>
   10550:	00040913          	addi	s2,s0,0
   10554:	f55ff06f          	jal	zero,104a8 <__sfp+0x38>
   10558:	1ac00593          	addi	a1,zero,428
   1055c:	00098513          	addi	a0,s3,0
   10560:	655000ef          	jal	ra,113b4 <_malloc_r>
   10564:	00050413          	addi	s0,a0,0
   10568:	02050c63          	beq	a0,zero,105a0 <__sfp+0x130>
   1056c:	00400793          	addi	a5,zero,4
   10570:	00c50513          	addi	a0,a0,12
   10574:	00042023          	sw	zero,0(s0)
   10578:	00f42223          	sw	a5,4(s0)
   1057c:	00a42423          	sw	a0,8(s0)
   10580:	1a000613          	addi	a2,zero,416
   10584:	00000593          	addi	a1,zero,0
   10588:	6f4000ef          	jal	ra,10c7c <memset>
   1058c:	00892023          	sw	s0,0(s2)
   10590:	00040913          	addi	s2,s0,0
   10594:	f15ff06f          	jal	zero,104a8 <__sfp+0x38>
   10598:	d71ff0ef          	jal	ra,10308 <global_stdio_init.part.0>
   1059c:	f01ff06f          	jal	zero,1049c <__sfp+0x2c>
   105a0:	00092023          	sw	zero,0(s2)
   105a4:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   105a8:	6d0000ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   105ac:	00c00793          	addi	a5,zero,12
   105b0:	00f9a023          	sw	a5,0(s3)
   105b4:	f75ff06f          	jal	zero,10528 <__sfp+0xb8>

000105b8 <__sinit>:
   105b8:	ff010113          	addi	sp,sp,-16
   105bc:	00812423          	sw	s0,8(sp)
   105c0:	00050413          	addi	s0,a0,0
   105c4:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   105c8:	00112623          	sw	ra,12(sp)
   105cc:	694000ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   105d0:	03442783          	lw	a5,52(s0)
   105d4:	00079c63          	bne	a5,zero,105ec <__sinit+0x34>
   105d8:	d501a783          	lw	a5,-688(gp) # 138f0 <__stdio_exit_handler>
   105dc:	00000717          	auipc	a4,0x0
   105e0:	c4870713          	addi	a4,a4,-952 # 10224 <cleanup_stdio>
   105e4:	02e42a23          	sw	a4,52(s0)
   105e8:	00078c63          	beq	a5,zero,10600 <__sinit+0x48>
   105ec:	00812403          	lw	s0,8(sp)
   105f0:	00c12083          	lw	ra,12(sp)
   105f4:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   105f8:	01010113          	addi	sp,sp,16
   105fc:	67c0006f          	jal	zero,10c78 <__retarget_lock_release_recursive>
   10600:	d09ff0ef          	jal	ra,10308 <global_stdio_init.part.0>
   10604:	00812403          	lw	s0,8(sp)
   10608:	00c12083          	lw	ra,12(sp)
   1060c:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   10610:	01010113          	addi	sp,sp,16
   10614:	6640006f          	jal	zero,10c78 <__retarget_lock_release_recursive>

00010618 <__sfp_lock_acquire>:
   10618:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   1061c:	6440006f          	jal	zero,10c60 <__retarget_lock_acquire_recursive>

00010620 <__sfp_lock_release>:
   10620:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   10624:	6540006f          	jal	zero,10c78 <__retarget_lock_release_recursive>

00010628 <__fp_lock_all>:
   10628:	ff010113          	addi	sp,sp,-16
   1062c:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   10630:	00112623          	sw	ra,12(sp)
   10634:	62c000ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   10638:	00c12083          	lw	ra,12(sp)
   1063c:	00003617          	auipc	a2,0x3
   10640:	d6460613          	addi	a2,a2,-668 # 133a0 <__sglue>
   10644:	00000597          	auipc	a1,0x0
   10648:	c4458593          	addi	a1,a1,-956 # 10288 <__fp_lock>
   1064c:	00000513          	addi	a0,zero,0
   10650:	01010113          	addi	sp,sp,16
   10654:	0340006f          	jal	zero,10688 <_fwalk_sglue>

00010658 <__fp_unlock_all>:
   10658:	ff010113          	addi	sp,sp,-16
   1065c:	00003617          	auipc	a2,0x3
   10660:	d4460613          	addi	a2,a2,-700 # 133a0 <__sglue>
   10664:	00000597          	auipc	a1,0x0
   10668:	c6458593          	addi	a1,a1,-924 # 102c8 <__fp_unlock>
   1066c:	00000513          	addi	a0,zero,0
   10670:	00112623          	sw	ra,12(sp)
   10674:	014000ef          	jal	ra,10688 <_fwalk_sglue>
   10678:	00c12083          	lw	ra,12(sp)
   1067c:	d7418513          	addi	a0,gp,-652 # 13914 <__lock___sfp_recursive_mutex>
   10680:	01010113          	addi	sp,sp,16
   10684:	5f40006f          	jal	zero,10c78 <__retarget_lock_release_recursive>

00010688 <_fwalk_sglue>:
   10688:	fd010113          	addi	sp,sp,-48
   1068c:	03212023          	sw	s2,32(sp)
   10690:	01312e23          	sw	s3,28(sp)
   10694:	01412c23          	sw	s4,24(sp)
   10698:	01512a23          	sw	s5,20(sp)
   1069c:	01612823          	sw	s6,16(sp)
   106a0:	01712623          	sw	s7,12(sp)
   106a4:	02112623          	sw	ra,44(sp)
   106a8:	02812423          	sw	s0,40(sp)
   106ac:	02912223          	sw	s1,36(sp)
   106b0:	00050b13          	addi	s6,a0,0
   106b4:	00058b93          	addi	s7,a1,0
   106b8:	00060a93          	addi	s5,a2,0
   106bc:	00000a13          	addi	s4,zero,0
   106c0:	00100993          	addi	s3,zero,1
   106c4:	fff00913          	addi	s2,zero,-1
   106c8:	004aa483          	lw	s1,4(s5)
   106cc:	008aa403          	lw	s0,8(s5)
   106d0:	fff48493          	addi	s1,s1,-1
   106d4:	0204c863          	blt	s1,zero,10704 <_fwalk_sglue+0x7c>
   106d8:	00c45783          	lhu	a5,12(s0)
   106dc:	00f9fe63          	bgeu	s3,a5,106f8 <_fwalk_sglue+0x70>
   106e0:	00e41783          	lh	a5,14(s0)
   106e4:	00040593          	addi	a1,s0,0
   106e8:	000b0513          	addi	a0,s6,0
   106ec:	01278663          	beq	a5,s2,106f8 <_fwalk_sglue+0x70>
   106f0:	000b80e7          	jalr	ra,0(s7)
   106f4:	00aa6a33          	or	s4,s4,a0
   106f8:	fff48493          	addi	s1,s1,-1
   106fc:	06840413          	addi	s0,s0,104
   10700:	fd249ce3          	bne	s1,s2,106d8 <_fwalk_sglue+0x50>
   10704:	000aaa83          	lw	s5,0(s5)
   10708:	fc0a90e3          	bne	s5,zero,106c8 <_fwalk_sglue+0x40>
   1070c:	02c12083          	lw	ra,44(sp)
   10710:	02812403          	lw	s0,40(sp)
   10714:	02412483          	lw	s1,36(sp)
   10718:	02012903          	lw	s2,32(sp)
   1071c:	01c12983          	lw	s3,28(sp)
   10720:	01412a83          	lw	s5,20(sp)
   10724:	01012b03          	lw	s6,16(sp)
   10728:	00c12b83          	lw	s7,12(sp)
   1072c:	000a0513          	addi	a0,s4,0
   10730:	01812a03          	lw	s4,24(sp)
   10734:	03010113          	addi	sp,sp,48
   10738:	00008067          	jalr	zero,0(ra)

0001073c <__sread>:
   1073c:	ff010113          	addi	sp,sp,-16
   10740:	00812423          	sw	s0,8(sp)
   10744:	00058413          	addi	s0,a1,0
   10748:	00e59583          	lh	a1,14(a1)
   1074c:	00112623          	sw	ra,12(sp)
   10750:	314000ef          	jal	ra,10a64 <_read_r>
   10754:	02054063          	blt	a0,zero,10774 <__sread+0x38>
   10758:	05042783          	lw	a5,80(s0)
   1075c:	00c12083          	lw	ra,12(sp)
   10760:	00a787b3          	add	a5,a5,a0
   10764:	04f42823          	sw	a5,80(s0)
   10768:	00812403          	lw	s0,8(sp)
   1076c:	01010113          	addi	sp,sp,16
   10770:	00008067          	jalr	zero,0(ra)
   10774:	00c45783          	lhu	a5,12(s0)
   10778:	fffff737          	lui	a4,0xfffff
   1077c:	fff70713          	addi	a4,a4,-1 # ffffefff <__BSS_END__+0xfffeb3cb>
   10780:	00e7f7b3          	and	a5,a5,a4
   10784:	00c12083          	lw	ra,12(sp)
   10788:	00f41623          	sh	a5,12(s0)
   1078c:	00812403          	lw	s0,8(sp)
   10790:	01010113          	addi	sp,sp,16
   10794:	00008067          	jalr	zero,0(ra)

00010798 <__seofread>:
   10798:	00000513          	addi	a0,zero,0
   1079c:	00008067          	jalr	zero,0(ra)

000107a0 <__swrite>:
   107a0:	00c59783          	lh	a5,12(a1)
   107a4:	fe010113          	addi	sp,sp,-32
   107a8:	00812c23          	sw	s0,24(sp)
   107ac:	00912a23          	sw	s1,20(sp)
   107b0:	01212823          	sw	s2,16(sp)
   107b4:	01312623          	sw	s3,12(sp)
   107b8:	00112e23          	sw	ra,28(sp)
   107bc:	1007f713          	andi	a4,a5,256
   107c0:	00058413          	addi	s0,a1,0
   107c4:	00060913          	addi	s2,a2,0
   107c8:	00068993          	addi	s3,a3,0
   107cc:	00050493          	addi	s1,a0,0
   107d0:	04071063          	bne	a4,zero,10810 <__swrite+0x70>
   107d4:	fffff737          	lui	a4,0xfffff
   107d8:	fff70713          	addi	a4,a4,-1 # ffffefff <__BSS_END__+0xfffeb3cb>
   107dc:	00e7f7b3          	and	a5,a5,a4
   107e0:	00e41583          	lh	a1,14(s0)
   107e4:	00f41623          	sh	a5,12(s0)
   107e8:	01812403          	lw	s0,24(sp)
   107ec:	01c12083          	lw	ra,28(sp)
   107f0:	00098693          	addi	a3,s3,0
   107f4:	00090613          	addi	a2,s2,0
   107f8:	00c12983          	lw	s3,12(sp)
   107fc:	01012903          	lw	s2,16(sp)
   10800:	00048513          	addi	a0,s1,0
   10804:	01412483          	lw	s1,20(sp)
   10808:	02010113          	addi	sp,sp,32
   1080c:	2d40006f          	jal	zero,10ae0 <_write_r>
   10810:	00e59583          	lh	a1,14(a1)
   10814:	00200693          	addi	a3,zero,2
   10818:	00000613          	addi	a2,zero,0
   1081c:	1cc000ef          	jal	ra,109e8 <_lseek_r>
   10820:	00c41783          	lh	a5,12(s0)
   10824:	fb1ff06f          	jal	zero,107d4 <__swrite+0x34>

00010828 <__sseek>:
   10828:	ff010113          	addi	sp,sp,-16
   1082c:	00812423          	sw	s0,8(sp)
   10830:	00058413          	addi	s0,a1,0
   10834:	00e59583          	lh	a1,14(a1)
   10838:	00112623          	sw	ra,12(sp)
   1083c:	1ac000ef          	jal	ra,109e8 <_lseek_r>
   10840:	fff00713          	addi	a4,zero,-1
   10844:	00c41783          	lh	a5,12(s0)
   10848:	02e50263          	beq	a0,a4,1086c <__sseek+0x44>
   1084c:	00001737          	lui	a4,0x1
   10850:	00e7e7b3          	or	a5,a5,a4
   10854:	00c12083          	lw	ra,12(sp)
   10858:	04a42823          	sw	a0,80(s0)
   1085c:	00f41623          	sh	a5,12(s0)
   10860:	00812403          	lw	s0,8(sp)
   10864:	01010113          	addi	sp,sp,16
   10868:	00008067          	jalr	zero,0(ra)
   1086c:	fffff737          	lui	a4,0xfffff
   10870:	fff70713          	addi	a4,a4,-1 # ffffefff <__BSS_END__+0xfffeb3cb>
   10874:	00e7f7b3          	and	a5,a5,a4
   10878:	00c12083          	lw	ra,12(sp)
   1087c:	00f41623          	sh	a5,12(s0)
   10880:	00812403          	lw	s0,8(sp)
   10884:	01010113          	addi	sp,sp,16
   10888:	00008067          	jalr	zero,0(ra)

0001088c <__sclose>:
   1088c:	00e59583          	lh	a1,14(a1)
   10890:	0040006f          	jal	zero,10894 <_close_r>

00010894 <_close_r>:
   10894:	ff010113          	addi	sp,sp,-16
   10898:	00812423          	sw	s0,8(sp)
   1089c:	00050413          	addi	s0,a0,0
   108a0:	00058513          	addi	a0,a1,0
   108a4:	d401aa23          	sw	zero,-684(gp) # 138f4 <errno>
   108a8:	00112623          	sw	ra,12(sp)
   108ac:	11d010ef          	jal	ra,121c8 <_close>
   108b0:	fff00793          	addi	a5,zero,-1
   108b4:	00f50a63          	beq	a0,a5,108c8 <_close_r+0x34>
   108b8:	00c12083          	lw	ra,12(sp)
   108bc:	00812403          	lw	s0,8(sp)
   108c0:	01010113          	addi	sp,sp,16
   108c4:	00008067          	jalr	zero,0(ra)
   108c8:	00912223          	sw	s1,4(sp)
   108cc:	d5418493          	addi	s1,gp,-684 # 138f4 <errno>
   108d0:	0004a783          	lw	a5,0(s1)
   108d4:	00078e63          	beq	a5,zero,108f0 <_close_r+0x5c>
   108d8:	00c12083          	lw	ra,12(sp)
   108dc:	00f42023          	sw	a5,0(s0)
   108e0:	00812403          	lw	s0,8(sp)
   108e4:	00412483          	lw	s1,4(sp)
   108e8:	01010113          	addi	sp,sp,16
   108ec:	00008067          	jalr	zero,0(ra)
   108f0:	00c12083          	lw	ra,12(sp)
   108f4:	00812403          	lw	s0,8(sp)
   108f8:	00412483          	lw	s1,4(sp)
   108fc:	01010113          	addi	sp,sp,16
   10900:	00008067          	jalr	zero,0(ra)

00010904 <_reclaim_reent>:
   10904:	d3c1a783          	lw	a5,-708(gp) # 138dc <_impure_ptr>
   10908:	0ca78e63          	beq	a5,a0,109e4 <_reclaim_reent+0xe0>
   1090c:	04452583          	lw	a1,68(a0)
   10910:	fe010113          	addi	sp,sp,-32
   10914:	00912a23          	sw	s1,20(sp)
   10918:	00112e23          	sw	ra,28(sp)
   1091c:	00812c23          	sw	s0,24(sp)
   10920:	00050493          	addi	s1,a0,0
   10924:	04058863          	beq	a1,zero,10974 <_reclaim_reent+0x70>
   10928:	01212823          	sw	s2,16(sp)
   1092c:	01312623          	sw	s3,12(sp)
   10930:	00000913          	addi	s2,zero,0
   10934:	08000993          	addi	s3,zero,128
   10938:	012587b3          	add	a5,a1,s2
   1093c:	0007a403          	lw	s0,0(a5)
   10940:	00040e63          	beq	s0,zero,1095c <_reclaim_reent+0x58>
   10944:	00040593          	addi	a1,s0,0
   10948:	00042403          	lw	s0,0(s0)
   1094c:	00048513          	addi	a0,s1,0
   10950:	774000ef          	jal	ra,110c4 <_free_r>
   10954:	fe0418e3          	bne	s0,zero,10944 <_reclaim_reent+0x40>
   10958:	0444a583          	lw	a1,68(s1)
   1095c:	00490913          	addi	s2,s2,4
   10960:	fd391ce3          	bne	s2,s3,10938 <_reclaim_reent+0x34>
   10964:	00048513          	addi	a0,s1,0
   10968:	75c000ef          	jal	ra,110c4 <_free_r>
   1096c:	01012903          	lw	s2,16(sp)
   10970:	00c12983          	lw	s3,12(sp)
   10974:	0384a583          	lw	a1,56(s1)
   10978:	00058663          	beq	a1,zero,10984 <_reclaim_reent+0x80>
   1097c:	00048513          	addi	a0,s1,0
   10980:	744000ef          	jal	ra,110c4 <_free_r>
   10984:	0404a403          	lw	s0,64(s1)
   10988:	00040c63          	beq	s0,zero,109a0 <_reclaim_reent+0x9c>
   1098c:	00040593          	addi	a1,s0,0
   10990:	00042403          	lw	s0,0(s0)
   10994:	00048513          	addi	a0,s1,0
   10998:	72c000ef          	jal	ra,110c4 <_free_r>
   1099c:	fe0418e3          	bne	s0,zero,1098c <_reclaim_reent+0x88>
   109a0:	04c4a583          	lw	a1,76(s1)
   109a4:	00058663          	beq	a1,zero,109b0 <_reclaim_reent+0xac>
   109a8:	00048513          	addi	a0,s1,0
   109ac:	718000ef          	jal	ra,110c4 <_free_r>
   109b0:	0344a783          	lw	a5,52(s1)
   109b4:	00078e63          	beq	a5,zero,109d0 <_reclaim_reent+0xcc>
   109b8:	01812403          	lw	s0,24(sp)
   109bc:	01c12083          	lw	ra,28(sp)
   109c0:	00048513          	addi	a0,s1,0
   109c4:	01412483          	lw	s1,20(sp)
   109c8:	02010113          	addi	sp,sp,32
   109cc:	00078067          	jalr	zero,0(a5)
   109d0:	01c12083          	lw	ra,28(sp)
   109d4:	01812403          	lw	s0,24(sp)
   109d8:	01412483          	lw	s1,20(sp)
   109dc:	02010113          	addi	sp,sp,32
   109e0:	00008067          	jalr	zero,0(ra)
   109e4:	00008067          	jalr	zero,0(ra)

000109e8 <_lseek_r>:
   109e8:	ff010113          	addi	sp,sp,-16
   109ec:	00058713          	addi	a4,a1,0
   109f0:	00812423          	sw	s0,8(sp)
   109f4:	00060593          	addi	a1,a2,0
   109f8:	00050413          	addi	s0,a0,0
   109fc:	00068613          	addi	a2,a3,0
   10a00:	00070513          	addi	a0,a4,0
   10a04:	d401aa23          	sw	zero,-684(gp) # 138f4 <errno>
   10a08:	00112623          	sw	ra,12(sp)
   10a0c:	031010ef          	jal	ra,1223c <_lseek>
   10a10:	fff00793          	addi	a5,zero,-1
   10a14:	00f50a63          	beq	a0,a5,10a28 <_lseek_r+0x40>
   10a18:	00c12083          	lw	ra,12(sp)
   10a1c:	00812403          	lw	s0,8(sp)
   10a20:	01010113          	addi	sp,sp,16
   10a24:	00008067          	jalr	zero,0(ra)
   10a28:	00912223          	sw	s1,4(sp)
   10a2c:	d5418493          	addi	s1,gp,-684 # 138f4 <errno>
   10a30:	0004a783          	lw	a5,0(s1)
   10a34:	00078e63          	beq	a5,zero,10a50 <_lseek_r+0x68>
   10a38:	00c12083          	lw	ra,12(sp)
   10a3c:	00f42023          	sw	a5,0(s0)
   10a40:	00812403          	lw	s0,8(sp)
   10a44:	00412483          	lw	s1,4(sp)
   10a48:	01010113          	addi	sp,sp,16
   10a4c:	00008067          	jalr	zero,0(ra)
   10a50:	00c12083          	lw	ra,12(sp)
   10a54:	00812403          	lw	s0,8(sp)
   10a58:	00412483          	lw	s1,4(sp)
   10a5c:	01010113          	addi	sp,sp,16
   10a60:	00008067          	jalr	zero,0(ra)

00010a64 <_read_r>:
   10a64:	ff010113          	addi	sp,sp,-16
   10a68:	00058713          	addi	a4,a1,0
   10a6c:	00812423          	sw	s0,8(sp)
   10a70:	00060593          	addi	a1,a2,0
   10a74:	00050413          	addi	s0,a0,0
   10a78:	00068613          	addi	a2,a3,0
   10a7c:	00070513          	addi	a0,a4,0
   10a80:	d401aa23          	sw	zero,-684(gp) # 138f4 <errno>
   10a84:	00112623          	sw	ra,12(sp)
   10a88:	7f8010ef          	jal	ra,12280 <_read>
   10a8c:	fff00793          	addi	a5,zero,-1
   10a90:	00f50a63          	beq	a0,a5,10aa4 <_read_r+0x40>
   10a94:	00c12083          	lw	ra,12(sp)
   10a98:	00812403          	lw	s0,8(sp)
   10a9c:	01010113          	addi	sp,sp,16
   10aa0:	00008067          	jalr	zero,0(ra)
   10aa4:	00912223          	sw	s1,4(sp)
   10aa8:	d5418493          	addi	s1,gp,-684 # 138f4 <errno>
   10aac:	0004a783          	lw	a5,0(s1)
   10ab0:	00078e63          	beq	a5,zero,10acc <_read_r+0x68>
   10ab4:	00c12083          	lw	ra,12(sp)
   10ab8:	00f42023          	sw	a5,0(s0)
   10abc:	00812403          	lw	s0,8(sp)
   10ac0:	00412483          	lw	s1,4(sp)
   10ac4:	01010113          	addi	sp,sp,16
   10ac8:	00008067          	jalr	zero,0(ra)
   10acc:	00c12083          	lw	ra,12(sp)
   10ad0:	00812403          	lw	s0,8(sp)
   10ad4:	00412483          	lw	s1,4(sp)
   10ad8:	01010113          	addi	sp,sp,16
   10adc:	00008067          	jalr	zero,0(ra)

00010ae0 <_write_r>:
   10ae0:	ff010113          	addi	sp,sp,-16
   10ae4:	00058713          	addi	a4,a1,0
   10ae8:	00812423          	sw	s0,8(sp)
   10aec:	00060593          	addi	a1,a2,0
   10af0:	00050413          	addi	s0,a0,0
   10af4:	00068613          	addi	a2,a3,0
   10af8:	00070513          	addi	a0,a4,0
   10afc:	d401aa23          	sw	zero,-684(gp) # 138f4 <errno>
   10b00:	00112623          	sw	ra,12(sp)
   10b04:	03d010ef          	jal	ra,12340 <_write>
   10b08:	fff00793          	addi	a5,zero,-1
   10b0c:	00f50a63          	beq	a0,a5,10b20 <_write_r+0x40>
   10b10:	00c12083          	lw	ra,12(sp)
   10b14:	00812403          	lw	s0,8(sp)
   10b18:	01010113          	addi	sp,sp,16
   10b1c:	00008067          	jalr	zero,0(ra)
   10b20:	00912223          	sw	s1,4(sp)
   10b24:	d5418493          	addi	s1,gp,-684 # 138f4 <errno>
   10b28:	0004a783          	lw	a5,0(s1)
   10b2c:	00078e63          	beq	a5,zero,10b48 <_write_r+0x68>
   10b30:	00c12083          	lw	ra,12(sp)
   10b34:	00f42023          	sw	a5,0(s0)
   10b38:	00812403          	lw	s0,8(sp)
   10b3c:	00412483          	lw	s1,4(sp)
   10b40:	01010113          	addi	sp,sp,16
   10b44:	00008067          	jalr	zero,0(ra)
   10b48:	00c12083          	lw	ra,12(sp)
   10b4c:	00812403          	lw	s0,8(sp)
   10b50:	00412483          	lw	s1,4(sp)
   10b54:	01010113          	addi	sp,sp,16
   10b58:	00008067          	jalr	zero,0(ra)

00010b5c <__libc_init_array>:
   10b5c:	ff010113          	addi	sp,sp,-16
   10b60:	00812423          	sw	s0,8(sp)
   10b64:	01212023          	sw	s2,0(sp)
   10b68:	00003797          	auipc	a5,0x3
   10b6c:	82878793          	addi	a5,a5,-2008 # 13390 <__init_array_start>
   10b70:	00003417          	auipc	s0,0x3
   10b74:	82040413          	addi	s0,s0,-2016 # 13390 <__init_array_start>
   10b78:	00112623          	sw	ra,12(sp)
   10b7c:	00912223          	sw	s1,4(sp)
   10b80:	40878933          	sub	s2,a5,s0
   10b84:	02878063          	beq	a5,s0,10ba4 <__libc_init_array+0x48>
   10b88:	40295913          	srai	s2,s2,0x2
   10b8c:	00000493          	addi	s1,zero,0
   10b90:	00042783          	lw	a5,0(s0)
   10b94:	00148493          	addi	s1,s1,1
   10b98:	00440413          	addi	s0,s0,4
   10b9c:	000780e7          	jalr	ra,0(a5)
   10ba0:	ff24e8e3          	bltu	s1,s2,10b90 <__libc_init_array+0x34>
   10ba4:	00002797          	auipc	a5,0x2
   10ba8:	7f478793          	addi	a5,a5,2036 # 13398 <__do_global_dtors_aux_fini_array_entry>
   10bac:	00002417          	auipc	s0,0x2
   10bb0:	7e440413          	addi	s0,s0,2020 # 13390 <__init_array_start>
   10bb4:	40878933          	sub	s2,a5,s0
   10bb8:	40295913          	srai	s2,s2,0x2
   10bbc:	00878e63          	beq	a5,s0,10bd8 <__libc_init_array+0x7c>
   10bc0:	00000493          	addi	s1,zero,0
   10bc4:	00042783          	lw	a5,0(s0)
   10bc8:	00148493          	addi	s1,s1,1
   10bcc:	00440413          	addi	s0,s0,4
   10bd0:	000780e7          	jalr	ra,0(a5)
   10bd4:	ff24e8e3          	bltu	s1,s2,10bc4 <__libc_init_array+0x68>
   10bd8:	00c12083          	lw	ra,12(sp)
   10bdc:	00812403          	lw	s0,8(sp)
   10be0:	00412483          	lw	s1,4(sp)
   10be4:	00012903          	lw	s2,0(sp)
   10be8:	01010113          	addi	sp,sp,16
   10bec:	00008067          	jalr	zero,0(ra)

00010bf0 <__libc_fini_array>:
   10bf0:	ff010113          	addi	sp,sp,-16
   10bf4:	00812423          	sw	s0,8(sp)
   10bf8:	00002797          	auipc	a5,0x2
   10bfc:	7a078793          	addi	a5,a5,1952 # 13398 <__do_global_dtors_aux_fini_array_entry>
   10c00:	00002417          	auipc	s0,0x2
   10c04:	79c40413          	addi	s0,s0,1948 # 1339c <__fini_array_end>
   10c08:	40f40433          	sub	s0,s0,a5
   10c0c:	00912223          	sw	s1,4(sp)
   10c10:	00112623          	sw	ra,12(sp)
   10c14:	40245493          	srai	s1,s0,0x2
   10c18:	02048063          	beq	s1,zero,10c38 <__libc_fini_array+0x48>
   10c1c:	ffc40413          	addi	s0,s0,-4
   10c20:	00f40433          	add	s0,s0,a5
   10c24:	00042783          	lw	a5,0(s0)
   10c28:	fff48493          	addi	s1,s1,-1
   10c2c:	ffc40413          	addi	s0,s0,-4
   10c30:	000780e7          	jalr	ra,0(a5)
   10c34:	fe0498e3          	bne	s1,zero,10c24 <__libc_fini_array+0x34>
   10c38:	00c12083          	lw	ra,12(sp)
   10c3c:	00812403          	lw	s0,8(sp)
   10c40:	00412483          	lw	s1,4(sp)
   10c44:	01010113          	addi	sp,sp,16
   10c48:	00008067          	jalr	zero,0(ra)

00010c4c <__retarget_lock_init>:
   10c4c:	00008067          	jalr	zero,0(ra)

00010c50 <__retarget_lock_init_recursive>:
   10c50:	00008067          	jalr	zero,0(ra)

00010c54 <__retarget_lock_close>:
   10c54:	00008067          	jalr	zero,0(ra)

00010c58 <__retarget_lock_close_recursive>:
   10c58:	00008067          	jalr	zero,0(ra)

00010c5c <__retarget_lock_acquire>:
   10c5c:	00008067          	jalr	zero,0(ra)

00010c60 <__retarget_lock_acquire_recursive>:
   10c60:	00008067          	jalr	zero,0(ra)

00010c64 <__retarget_lock_try_acquire>:
   10c64:	00100513          	addi	a0,zero,1
   10c68:	00008067          	jalr	zero,0(ra)

00010c6c <__retarget_lock_try_acquire_recursive>:
   10c6c:	00100513          	addi	a0,zero,1
   10c70:	00008067          	jalr	zero,0(ra)

00010c74 <__retarget_lock_release>:
   10c74:	00008067          	jalr	zero,0(ra)

00010c78 <__retarget_lock_release_recursive>:
   10c78:	00008067          	jalr	zero,0(ra)

00010c7c <memset>:
   10c7c:	00f00313          	addi	t1,zero,15
   10c80:	00050713          	addi	a4,a0,0
   10c84:	02c37e63          	bgeu	t1,a2,10cc0 <memset+0x44>
   10c88:	00f77793          	andi	a5,a4,15
   10c8c:	0a079063          	bne	a5,zero,10d2c <memset+0xb0>
   10c90:	08059263          	bne	a1,zero,10d14 <memset+0x98>
   10c94:	ff067693          	andi	a3,a2,-16
   10c98:	00f67613          	andi	a2,a2,15
   10c9c:	00e686b3          	add	a3,a3,a4
   10ca0:	00b72023          	sw	a1,0(a4)
   10ca4:	00b72223          	sw	a1,4(a4)
   10ca8:	00b72423          	sw	a1,8(a4)
   10cac:	00b72623          	sw	a1,12(a4)
   10cb0:	01070713          	addi	a4,a4,16
   10cb4:	fed766e3          	bltu	a4,a3,10ca0 <memset+0x24>
   10cb8:	00061463          	bne	a2,zero,10cc0 <memset+0x44>
   10cbc:	00008067          	jalr	zero,0(ra)
   10cc0:	40c306b3          	sub	a3,t1,a2
   10cc4:	00269693          	slli	a3,a3,0x2
   10cc8:	00000297          	auipc	t0,0x0
   10ccc:	005686b3          	add	a3,a3,t0
   10cd0:	00c68067          	jalr	zero,12(a3)
   10cd4:	00b70723          	sb	a1,14(a4)
   10cd8:	00b706a3          	sb	a1,13(a4)
   10cdc:	00b70623          	sb	a1,12(a4)
   10ce0:	00b705a3          	sb	a1,11(a4)
   10ce4:	00b70523          	sb	a1,10(a4)
   10ce8:	00b704a3          	sb	a1,9(a4)
   10cec:	00b70423          	sb	a1,8(a4)
   10cf0:	00b703a3          	sb	a1,7(a4)
   10cf4:	00b70323          	sb	a1,6(a4)
   10cf8:	00b702a3          	sb	a1,5(a4)
   10cfc:	00b70223          	sb	a1,4(a4)
   10d00:	00b701a3          	sb	a1,3(a4)
   10d04:	00b70123          	sb	a1,2(a4)
   10d08:	00b700a3          	sb	a1,1(a4)
   10d0c:	00b70023          	sb	a1,0(a4)
   10d10:	00008067          	jalr	zero,0(ra)
   10d14:	0ff5f593          	andi	a1,a1,255
   10d18:	00859693          	slli	a3,a1,0x8
   10d1c:	00d5e5b3          	or	a1,a1,a3
   10d20:	01059693          	slli	a3,a1,0x10
   10d24:	00d5e5b3          	or	a1,a1,a3
   10d28:	f6dff06f          	jal	zero,10c94 <memset+0x18>
   10d2c:	00279693          	slli	a3,a5,0x2
   10d30:	00000297          	auipc	t0,0x0
   10d34:	005686b3          	add	a3,a3,t0
   10d38:	00008293          	addi	t0,ra,0
   10d3c:	fa0680e7          	jalr	ra,-96(a3)
   10d40:	00028093          	addi	ra,t0,0 # 10d30 <memset+0xb4>
   10d44:	ff078793          	addi	a5,a5,-16
   10d48:	40f70733          	sub	a4,a4,a5
   10d4c:	00f60633          	add	a2,a2,a5
   10d50:	f6c378e3          	bgeu	t1,a2,10cc0 <memset+0x44>
   10d54:	f3dff06f          	jal	zero,10c90 <memset+0x14>

00010d58 <__register_exitproc>:
   10d58:	fe010113          	addi	sp,sp,-32
   10d5c:	01212823          	sw	s2,16(sp)
   10d60:	d4018913          	addi	s2,gp,-704 # 138e0 <__atexit_recursive_mutex>
   10d64:	00812c23          	sw	s0,24(sp)
   10d68:	00050413          	addi	s0,a0,0
   10d6c:	00092503          	lw	a0,0(s2)
   10d70:	00912a23          	sw	s1,20(sp)
   10d74:	01312623          	sw	s3,12(sp)
   10d78:	01412423          	sw	s4,8(sp)
   10d7c:	00112e23          	sw	ra,28(sp)
   10d80:	00058493          	addi	s1,a1,0
   10d84:	00060a13          	addi	s4,a2,0
   10d88:	00068993          	addi	s3,a3,0
   10d8c:	ed5ff0ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   10d90:	d7818713          	addi	a4,gp,-648 # 13918 <__atexit>
   10d94:	00072783          	lw	a5,0(a4)
   10d98:	08078663          	beq	a5,zero,10e24 <__register_exitproc+0xcc>
   10d9c:	0047a703          	lw	a4,4(a5)
   10da0:	01f00593          	addi	a1,zero,31
   10da4:	00092503          	lw	a0,0(s2)
   10da8:	08e5c463          	blt	a1,a4,10e30 <__register_exitproc+0xd8>
   10dac:	00271593          	slli	a1,a4,0x2
   10db0:	02041e63          	bne	s0,zero,10dec <__register_exitproc+0x94>
   10db4:	00170713          	addi	a4,a4,1
   10db8:	00e7a223          	sw	a4,4(a5)
   10dbc:	00b787b3          	add	a5,a5,a1
   10dc0:	0097a423          	sw	s1,8(a5)
   10dc4:	eb5ff0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   10dc8:	00000513          	addi	a0,zero,0
   10dcc:	01c12083          	lw	ra,28(sp)
   10dd0:	01812403          	lw	s0,24(sp)
   10dd4:	01412483          	lw	s1,20(sp)
   10dd8:	01012903          	lw	s2,16(sp)
   10ddc:	00c12983          	lw	s3,12(sp)
   10de0:	00812a03          	lw	s4,8(sp)
   10de4:	02010113          	addi	sp,sp,32
   10de8:	00008067          	jalr	zero,0(ra)
   10dec:	00b78833          	add	a6,a5,a1
   10df0:	09482423          	sw	s4,136(a6)
   10df4:	1887a683          	lw	a3,392(a5)
   10df8:	00100613          	addi	a2,zero,1
   10dfc:	00e61633          	sll	a2,a2,a4
   10e00:	00c6e6b3          	or	a3,a3,a2
   10e04:	18d7a423          	sw	a3,392(a5)
   10e08:	11382423          	sw	s3,264(a6)
   10e0c:	00200693          	addi	a3,zero,2
   10e10:	fad412e3          	bne	s0,a3,10db4 <__register_exitproc+0x5c>
   10e14:	18c7a683          	lw	a3,396(a5)
   10e18:	00c6e6b3          	or	a3,a3,a2
   10e1c:	18d7a623          	sw	a3,396(a5)
   10e20:	f95ff06f          	jal	zero,10db4 <__register_exitproc+0x5c>
   10e24:	edc18793          	addi	a5,gp,-292 # 13a7c <__atexit0>
   10e28:	00f72023          	sw	a5,0(a4)
   10e2c:	f71ff06f          	jal	zero,10d9c <__register_exitproc+0x44>
   10e30:	e49ff0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   10e34:	fff00513          	addi	a0,zero,-1
   10e38:	f95ff06f          	jal	zero,10dcc <__register_exitproc+0x74>

00010e3c <__call_exitprocs>:
   10e3c:	fd010113          	addi	sp,sp,-48
   10e40:	01712623          	sw	s7,12(sp)
   10e44:	d4018b93          	addi	s7,gp,-704 # 138e0 <__atexit_recursive_mutex>
   10e48:	01612823          	sw	s6,16(sp)
   10e4c:	00050b13          	addi	s6,a0,0
   10e50:	000ba503          	lw	a0,0(s7)
   10e54:	01412c23          	sw	s4,24(sp)
   10e58:	d7818a13          	addi	s4,gp,-648 # 13918 <__atexit>
   10e5c:	03212023          	sw	s2,32(sp)
   10e60:	01812423          	sw	s8,8(sp)
   10e64:	02112623          	sw	ra,44(sp)
   10e68:	00058c13          	addi	s8,a1,0
   10e6c:	df5ff0ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   10e70:	000a2903          	lw	s2,0(s4)
   10e74:	06090063          	beq	s2,zero,10ed4 <__call_exitprocs+0x98>
   10e78:	01312e23          	sw	s3,28(sp)
   10e7c:	01512a23          	sw	s5,20(sp)
   10e80:	02812423          	sw	s0,40(sp)
   10e84:	02912223          	sw	s1,36(sp)
   10e88:	01912223          	sw	s9,4(sp)
   10e8c:	fff00993          	addi	s3,zero,-1
   10e90:	00100a93          	addi	s5,zero,1
   10e94:	00492483          	lw	s1,4(s2)
   10e98:	fff48413          	addi	s0,s1,-1
   10e9c:	02044263          	blt	s0,zero,10ec0 <__call_exitprocs+0x84>
   10ea0:	00249493          	slli	s1,s1,0x2
   10ea4:	009904b3          	add	s1,s2,s1
   10ea8:	040c0863          	beq	s8,zero,10ef8 <__call_exitprocs+0xbc>
   10eac:	1044a783          	lw	a5,260(s1)
   10eb0:	05878463          	beq	a5,s8,10ef8 <__call_exitprocs+0xbc>
   10eb4:	fff40413          	addi	s0,s0,-1
   10eb8:	ffc48493          	addi	s1,s1,-4
   10ebc:	ff3418e3          	bne	s0,s3,10eac <__call_exitprocs+0x70>
   10ec0:	02812403          	lw	s0,40(sp)
   10ec4:	02412483          	lw	s1,36(sp)
   10ec8:	01c12983          	lw	s3,28(sp)
   10ecc:	01412a83          	lw	s5,20(sp)
   10ed0:	00412c83          	lw	s9,4(sp)
   10ed4:	000ba503          	lw	a0,0(s7)
   10ed8:	02c12083          	lw	ra,44(sp)
   10edc:	02012903          	lw	s2,32(sp)
   10ee0:	01812a03          	lw	s4,24(sp)
   10ee4:	01012b03          	lw	s6,16(sp)
   10ee8:	00c12b83          	lw	s7,12(sp)
   10eec:	00812c03          	lw	s8,8(sp)
   10ef0:	03010113          	addi	sp,sp,48
   10ef4:	d85ff06f          	jal	zero,10c78 <__retarget_lock_release_recursive>
   10ef8:	00492783          	lw	a5,4(s2)
   10efc:	0044a683          	lw	a3,4(s1)
   10f00:	fff78793          	addi	a5,a5,-1
   10f04:	06878a63          	beq	a5,s0,10f78 <__call_exitprocs+0x13c>
   10f08:	0004a223          	sw	zero,4(s1)
   10f0c:	02068663          	beq	a3,zero,10f38 <__call_exitprocs+0xfc>
   10f10:	18892783          	lw	a5,392(s2)
   10f14:	008a9733          	sll	a4,s5,s0
   10f18:	00492c83          	lw	s9,4(s2)
   10f1c:	00f777b3          	and	a5,a4,a5
   10f20:	02079463          	bne	a5,zero,10f48 <__call_exitprocs+0x10c>
   10f24:	000680e7          	jalr	ra,0(a3)
   10f28:	00492703          	lw	a4,4(s2)
   10f2c:	000a2783          	lw	a5,0(s4)
   10f30:	03971e63          	bne	a4,s9,10f6c <__call_exitprocs+0x130>
   10f34:	03279c63          	bne	a5,s2,10f6c <__call_exitprocs+0x130>
   10f38:	fff40413          	addi	s0,s0,-1
   10f3c:	ffc48493          	addi	s1,s1,-4
   10f40:	f73414e3          	bne	s0,s3,10ea8 <__call_exitprocs+0x6c>
   10f44:	f7dff06f          	jal	zero,10ec0 <__call_exitprocs+0x84>
   10f48:	18c92783          	lw	a5,396(s2)
   10f4c:	0844a583          	lw	a1,132(s1)
   10f50:	00f77733          	and	a4,a4,a5
   10f54:	02071663          	bne	a4,zero,10f80 <__call_exitprocs+0x144>
   10f58:	000b0513          	addi	a0,s6,0
   10f5c:	000680e7          	jalr	ra,0(a3)
   10f60:	00492703          	lw	a4,4(s2)
   10f64:	000a2783          	lw	a5,0(s4)
   10f68:	fd9706e3          	beq	a4,s9,10f34 <__call_exitprocs+0xf8>
   10f6c:	f4078ae3          	beq	a5,zero,10ec0 <__call_exitprocs+0x84>
   10f70:	00078913          	addi	s2,a5,0
   10f74:	f21ff06f          	jal	zero,10e94 <__call_exitprocs+0x58>
   10f78:	00892223          	sw	s0,4(s2)
   10f7c:	f91ff06f          	jal	zero,10f0c <__call_exitprocs+0xd0>
   10f80:	00058513          	addi	a0,a1,0
   10f84:	000680e7          	jalr	ra,0(a3)
   10f88:	fa1ff06f          	jal	zero,10f28 <__call_exitprocs+0xec>

00010f8c <_malloc_trim_r>:
   10f8c:	fe010113          	addi	sp,sp,-32
   10f90:	00812c23          	sw	s0,24(sp)
   10f94:	00912a23          	sw	s1,20(sp)
   10f98:	01212823          	sw	s2,16(sp)
   10f9c:	01312623          	sw	s3,12(sp)
   10fa0:	01412423          	sw	s4,8(sp)
   10fa4:	00058993          	addi	s3,a1,0
   10fa8:	00112e23          	sw	ra,28(sp)
   10fac:	00050913          	addi	s2,a0,0
   10fb0:	00002a17          	auipc	s4,0x2
   10fb4:	520a0a13          	addi	s4,s4,1312 # 134d0 <__malloc_av_>
   10fb8:	411000ef          	jal	ra,11bc8 <__malloc_lock>
   10fbc:	008a2783          	lw	a5,8(s4)
   10fc0:	00001437          	lui	s0,0x1
   10fc4:	fef40413          	addi	s0,s0,-17 # fef <exit-0xf0c5>
   10fc8:	0047a483          	lw	s1,4(a5)
   10fcc:	000017b7          	lui	a5,0x1
   10fd0:	ffc4f493          	andi	s1,s1,-4
   10fd4:	00848433          	add	s0,s1,s0
   10fd8:	41340433          	sub	s0,s0,s3
   10fdc:	00c45413          	srli	s0,s0,0xc
   10fe0:	fff40413          	addi	s0,s0,-1
   10fe4:	00c41413          	slli	s0,s0,0xc
   10fe8:	00f44e63          	blt	s0,a5,11004 <_malloc_trim_r+0x78>
   10fec:	00000593          	addi	a1,zero,0
   10ff0:	00090513          	addi	a0,s2,0
   10ff4:	164010ef          	jal	ra,12158 <_sbrk_r>
   10ff8:	008a2783          	lw	a5,8(s4)
   10ffc:	009787b3          	add	a5,a5,s1
   11000:	02f50863          	beq	a0,a5,11030 <_malloc_trim_r+0xa4>
   11004:	00090513          	addi	a0,s2,0
   11008:	3c9000ef          	jal	ra,11bd0 <__malloc_unlock>
   1100c:	01c12083          	lw	ra,28(sp)
   11010:	01812403          	lw	s0,24(sp)
   11014:	01412483          	lw	s1,20(sp)
   11018:	01012903          	lw	s2,16(sp)
   1101c:	00c12983          	lw	s3,12(sp)
   11020:	00812a03          	lw	s4,8(sp)
   11024:	00000513          	addi	a0,zero,0
   11028:	02010113          	addi	sp,sp,32
   1102c:	00008067          	jalr	zero,0(ra)
   11030:	408005b3          	sub	a1,zero,s0
   11034:	00090513          	addi	a0,s2,0
   11038:	120010ef          	jal	ra,12158 <_sbrk_r>
   1103c:	fff00793          	addi	a5,zero,-1
   11040:	04f50863          	beq	a0,a5,11090 <_malloc_trim_r+0x104>
   11044:	06c18713          	addi	a4,gp,108 # 13c0c <__malloc_current_mallinfo>
   11048:	008a2683          	lw	a3,8(s4)
   1104c:	00072783          	lw	a5,0(a4)
   11050:	408484b3          	sub	s1,s1,s0
   11054:	0014e493          	ori	s1,s1,1
   11058:	00090513          	addi	a0,s2,0
   1105c:	408787b3          	sub	a5,a5,s0
   11060:	0096a223          	sw	s1,4(a3)
   11064:	00f72023          	sw	a5,0(a4)
   11068:	369000ef          	jal	ra,11bd0 <__malloc_unlock>
   1106c:	01c12083          	lw	ra,28(sp)
   11070:	01812403          	lw	s0,24(sp)
   11074:	01412483          	lw	s1,20(sp)
   11078:	01012903          	lw	s2,16(sp)
   1107c:	00c12983          	lw	s3,12(sp)
   11080:	00812a03          	lw	s4,8(sp)
   11084:	00100513          	addi	a0,zero,1
   11088:	02010113          	addi	sp,sp,32
   1108c:	00008067          	jalr	zero,0(ra)
   11090:	00000593          	addi	a1,zero,0
   11094:	00090513          	addi	a0,s2,0
   11098:	0c0010ef          	jal	ra,12158 <_sbrk_r>
   1109c:	008a2703          	lw	a4,8(s4)
   110a0:	00f00693          	addi	a3,zero,15
   110a4:	40e507b3          	sub	a5,a0,a4
   110a8:	f4f6dee3          	bge	a3,a5,11004 <_malloc_trim_r+0x78>
   110ac:	d441a683          	lw	a3,-700(gp) # 138e4 <__malloc_sbrk_base>
   110b0:	0017e793          	ori	a5,a5,1
   110b4:	00f72223          	sw	a5,4(a4)
   110b8:	40d50533          	sub	a0,a0,a3
   110bc:	06a1a623          	sw	a0,108(gp) # 13c0c <__malloc_current_mallinfo>
   110c0:	f45ff06f          	jal	zero,11004 <_malloc_trim_r+0x78>

000110c4 <_free_r>:
   110c4:	12058663          	beq	a1,zero,111f0 <_free_r+0x12c>
   110c8:	ff010113          	addi	sp,sp,-16
   110cc:	00812423          	sw	s0,8(sp)
   110d0:	00912223          	sw	s1,4(sp)
   110d4:	00058413          	addi	s0,a1,0
   110d8:	00050493          	addi	s1,a0,0
   110dc:	00112623          	sw	ra,12(sp)
   110e0:	2e9000ef          	jal	ra,11bc8 <__malloc_lock>
   110e4:	ffc42583          	lw	a1,-4(s0)
   110e8:	ff840713          	addi	a4,s0,-8
   110ec:	00002817          	auipc	a6,0x2
   110f0:	3e480813          	addi	a6,a6,996 # 134d0 <__malloc_av_>
   110f4:	ffe5f793          	andi	a5,a1,-2
   110f8:	00f70633          	add	a2,a4,a5
   110fc:	00462683          	lw	a3,4(a2)
   11100:	00882503          	lw	a0,8(a6)
   11104:	0015f893          	andi	a7,a1,1
   11108:	ffc6f693          	andi	a3,a3,-4
   1110c:	18c50c63          	beq	a0,a2,112a4 <_free_r+0x1e0>
   11110:	00d62223          	sw	a3,4(a2)
   11114:	00d60533          	add	a0,a2,a3
   11118:	00452503          	lw	a0,4(a0)
   1111c:	00157513          	andi	a0,a0,1
   11120:	08089c63          	bne	a7,zero,111b8 <_free_r+0xf4>
   11124:	ff842303          	lw	t1,-8(s0)
   11128:	00002897          	auipc	a7,0x2
   1112c:	3b088893          	addi	a7,a7,944 # 134d8 <__malloc_av_+0x8>
   11130:	40670733          	sub	a4,a4,t1
   11134:	00872583          	lw	a1,8(a4)
   11138:	006787b3          	add	a5,a5,t1
   1113c:	13158e63          	beq	a1,a7,11278 <_free_r+0x1b4>
   11140:	00c72303          	lw	t1,12(a4)
   11144:	0065a623          	sw	t1,12(a1)
   11148:	00b32423          	sw	a1,8(t1) # 101a0 <frame_dummy+0x1c>
   1114c:	1a050063          	beq	a0,zero,112ec <_free_r+0x228>
   11150:	0017e693          	ori	a3,a5,1
   11154:	00d72223          	sw	a3,4(a4)
   11158:	00f62023          	sw	a5,0(a2)
   1115c:	1ff00693          	addi	a3,zero,511
   11160:	0af6e463          	bltu	a3,a5,11208 <_free_r+0x144>
   11164:	ff87f693          	andi	a3,a5,-8
   11168:	00868693          	addi	a3,a3,8
   1116c:	00482583          	lw	a1,4(a6)
   11170:	00d806b3          	add	a3,a6,a3
   11174:	0006a603          	lw	a2,0(a3)
   11178:	0057d513          	srli	a0,a5,0x5
   1117c:	00100793          	addi	a5,zero,1
   11180:	00a797b3          	sll	a5,a5,a0
   11184:	00b7e7b3          	or	a5,a5,a1
   11188:	ff868593          	addi	a1,a3,-8
   1118c:	00c72423          	sw	a2,8(a4)
   11190:	00b72623          	sw	a1,12(a4)
   11194:	00f82223          	sw	a5,4(a6)
   11198:	00e6a023          	sw	a4,0(a3)
   1119c:	00e62623          	sw	a4,12(a2)
   111a0:	00812403          	lw	s0,8(sp)
   111a4:	00c12083          	lw	ra,12(sp)
   111a8:	00048513          	addi	a0,s1,0
   111ac:	00412483          	lw	s1,4(sp)
   111b0:	01010113          	addi	sp,sp,16
   111b4:	21d0006f          	jal	zero,11bd0 <__malloc_unlock>
   111b8:	02051e63          	bne	a0,zero,111f4 <_free_r+0x130>
   111bc:	00d787b3          	add	a5,a5,a3
   111c0:	00002897          	auipc	a7,0x2
   111c4:	31888893          	addi	a7,a7,792 # 134d8 <__malloc_av_+0x8>
   111c8:	00862683          	lw	a3,8(a2)
   111cc:	0017e513          	ori	a0,a5,1
   111d0:	00f705b3          	add	a1,a4,a5
   111d4:	17168263          	beq	a3,a7,11338 <_free_r+0x274>
   111d8:	00c62603          	lw	a2,12(a2)
   111dc:	00c6a623          	sw	a2,12(a3)
   111e0:	00d62423          	sw	a3,8(a2)
   111e4:	00a72223          	sw	a0,4(a4)
   111e8:	00f5a023          	sw	a5,0(a1)
   111ec:	f71ff06f          	jal	zero,1115c <_free_r+0x98>
   111f0:	00008067          	jalr	zero,0(ra)
   111f4:	0015e593          	ori	a1,a1,1
   111f8:	feb42e23          	sw	a1,-4(s0)
   111fc:	00f62023          	sw	a5,0(a2)
   11200:	1ff00693          	addi	a3,zero,511
   11204:	f6f6f0e3          	bgeu	a3,a5,11164 <_free_r+0xa0>
   11208:	0097d693          	srli	a3,a5,0x9
   1120c:	00400613          	addi	a2,zero,4
   11210:	0ed66263          	bltu	a2,a3,112f4 <_free_r+0x230>
   11214:	0067d693          	srli	a3,a5,0x6
   11218:	03968593          	addi	a1,a3,57
   1121c:	00359593          	slli	a1,a1,0x3
   11220:	03868613          	addi	a2,a3,56
   11224:	00b805b3          	add	a1,a6,a1
   11228:	0005a683          	lw	a3,0(a1)
   1122c:	ff858593          	addi	a1,a1,-8
   11230:	00d59863          	bne	a1,a3,11240 <_free_r+0x17c>
   11234:	1200006f          	jal	zero,11354 <_free_r+0x290>
   11238:	0086a683          	lw	a3,8(a3)
   1123c:	00d58863          	beq	a1,a3,1124c <_free_r+0x188>
   11240:	0046a603          	lw	a2,4(a3)
   11244:	ffc67613          	andi	a2,a2,-4
   11248:	fec7e8e3          	bltu	a5,a2,11238 <_free_r+0x174>
   1124c:	00c6a583          	lw	a1,12(a3)
   11250:	00b72623          	sw	a1,12(a4)
   11254:	00d72423          	sw	a3,8(a4)
   11258:	00812403          	lw	s0,8(sp)
   1125c:	00c12083          	lw	ra,12(sp)
   11260:	00e5a423          	sw	a4,8(a1)
   11264:	00048513          	addi	a0,s1,0
   11268:	00412483          	lw	s1,4(sp)
   1126c:	00e6a623          	sw	a4,12(a3)
   11270:	01010113          	addi	sp,sp,16
   11274:	15d0006f          	jal	zero,11bd0 <__malloc_unlock>
   11278:	0a051063          	bne	a0,zero,11318 <_free_r+0x254>
   1127c:	00c62583          	lw	a1,12(a2)
   11280:	00862603          	lw	a2,8(a2)
   11284:	00f686b3          	add	a3,a3,a5
   11288:	0016e793          	ori	a5,a3,1
   1128c:	00b62623          	sw	a1,12(a2)
   11290:	00c5a423          	sw	a2,8(a1)
   11294:	00f72223          	sw	a5,4(a4)
   11298:	00d70733          	add	a4,a4,a3
   1129c:	00d72023          	sw	a3,0(a4)
   112a0:	f01ff06f          	jal	zero,111a0 <_free_r+0xdc>
   112a4:	00d786b3          	add	a3,a5,a3
   112a8:	02089063          	bne	a7,zero,112c8 <_free_r+0x204>
   112ac:	ff842583          	lw	a1,-8(s0)
   112b0:	40b70733          	sub	a4,a4,a1
   112b4:	00c72783          	lw	a5,12(a4)
   112b8:	00872603          	lw	a2,8(a4)
   112bc:	00b686b3          	add	a3,a3,a1
   112c0:	00f62623          	sw	a5,12(a2)
   112c4:	00c7a423          	sw	a2,8(a5) # 1008 <exit-0xf0ac>
   112c8:	0016e613          	ori	a2,a3,1
   112cc:	d481a783          	lw	a5,-696(gp) # 138e8 <__malloc_trim_threshold>
   112d0:	00c72223          	sw	a2,4(a4)
   112d4:	00e82423          	sw	a4,8(a6)
   112d8:	ecf6e4e3          	bltu	a3,a5,111a0 <_free_r+0xdc>
   112dc:	d841a583          	lw	a1,-636(gp) # 13924 <__malloc_top_pad>
   112e0:	00048513          	addi	a0,s1,0
   112e4:	ca9ff0ef          	jal	ra,10f8c <_malloc_trim_r>
   112e8:	eb9ff06f          	jal	zero,111a0 <_free_r+0xdc>
   112ec:	00d787b3          	add	a5,a5,a3
   112f0:	ed9ff06f          	jal	zero,111c8 <_free_r+0x104>
   112f4:	01400613          	addi	a2,zero,20
   112f8:	02d67863          	bgeu	a2,a3,11328 <_free_r+0x264>
   112fc:	05400613          	addi	a2,zero,84
   11300:	06d66863          	bltu	a2,a3,11370 <_free_r+0x2ac>
   11304:	00c7d693          	srli	a3,a5,0xc
   11308:	06f68593          	addi	a1,a3,111
   1130c:	00359593          	slli	a1,a1,0x3
   11310:	06e68613          	addi	a2,a3,110
   11314:	f11ff06f          	jal	zero,11224 <_free_r+0x160>
   11318:	0017e693          	ori	a3,a5,1
   1131c:	00d72223          	sw	a3,4(a4)
   11320:	00f62023          	sw	a5,0(a2)
   11324:	e7dff06f          	jal	zero,111a0 <_free_r+0xdc>
   11328:	05c68593          	addi	a1,a3,92
   1132c:	00359593          	slli	a1,a1,0x3
   11330:	05b68613          	addi	a2,a3,91
   11334:	ef1ff06f          	jal	zero,11224 <_free_r+0x160>
   11338:	00e82a23          	sw	a4,20(a6)
   1133c:	00e82823          	sw	a4,16(a6)
   11340:	01172623          	sw	a7,12(a4)
   11344:	01172423          	sw	a7,8(a4)
   11348:	00a72223          	sw	a0,4(a4)
   1134c:	00f5a023          	sw	a5,0(a1)
   11350:	e51ff06f          	jal	zero,111a0 <_free_r+0xdc>
   11354:	00482503          	lw	a0,4(a6)
   11358:	40265613          	srai	a2,a2,0x2
   1135c:	00100793          	addi	a5,zero,1
   11360:	00c797b3          	sll	a5,a5,a2
   11364:	00a7e7b3          	or	a5,a5,a0
   11368:	00f82223          	sw	a5,4(a6)
   1136c:	ee5ff06f          	jal	zero,11250 <_free_r+0x18c>
   11370:	15400613          	addi	a2,zero,340
   11374:	00d66c63          	bltu	a2,a3,1138c <_free_r+0x2c8>
   11378:	00f7d693          	srli	a3,a5,0xf
   1137c:	07868593          	addi	a1,a3,120
   11380:	00359593          	slli	a1,a1,0x3
   11384:	07768613          	addi	a2,a3,119
   11388:	e9dff06f          	jal	zero,11224 <_free_r+0x160>
   1138c:	55400613          	addi	a2,zero,1364
   11390:	00d66c63          	bltu	a2,a3,113a8 <_free_r+0x2e4>
   11394:	0127d693          	srli	a3,a5,0x12
   11398:	07d68593          	addi	a1,a3,125
   1139c:	00359593          	slli	a1,a1,0x3
   113a0:	07c68613          	addi	a2,a3,124
   113a4:	e81ff06f          	jal	zero,11224 <_free_r+0x160>
   113a8:	3f800593          	addi	a1,zero,1016
   113ac:	07e00613          	addi	a2,zero,126
   113b0:	e75ff06f          	jal	zero,11224 <_free_r+0x160>

000113b4 <_malloc_r>:
   113b4:	fd010113          	addi	sp,sp,-48
   113b8:	03212023          	sw	s2,32(sp)
   113bc:	02112623          	sw	ra,44(sp)
   113c0:	02812423          	sw	s0,40(sp)
   113c4:	02912223          	sw	s1,36(sp)
   113c8:	01312e23          	sw	s3,28(sp)
   113cc:	00b58793          	addi	a5,a1,11
   113d0:	01600713          	addi	a4,zero,22
   113d4:	00050913          	addi	s2,a0,0
   113d8:	08f76063          	bltu	a4,a5,11458 <_malloc_r+0xa4>
   113dc:	01000493          	addi	s1,zero,16
   113e0:	20b4e463          	bltu	s1,a1,115e8 <_malloc_r+0x234>
   113e4:	7e4000ef          	jal	ra,11bc8 <__malloc_lock>
   113e8:	01800793          	addi	a5,zero,24
   113ec:	00200593          	addi	a1,zero,2
   113f0:	00002997          	auipc	s3,0x2
   113f4:	0e098993          	addi	s3,s3,224 # 134d0 <__malloc_av_>
   113f8:	00f987b3          	add	a5,s3,a5
   113fc:	0047a403          	lw	s0,4(a5)
   11400:	ff878713          	addi	a4,a5,-8
   11404:	44e40c63          	beq	s0,a4,1185c <_malloc_r+0x4a8>
   11408:	00442783          	lw	a5,4(s0)
   1140c:	00c42683          	lw	a3,12(s0)
   11410:	00842603          	lw	a2,8(s0)
   11414:	ffc7f793          	andi	a5,a5,-4
   11418:	00f407b3          	add	a5,s0,a5
   1141c:	0047a703          	lw	a4,4(a5)
   11420:	00d62623          	sw	a3,12(a2)
   11424:	00c6a423          	sw	a2,8(a3)
   11428:	00176713          	ori	a4,a4,1
   1142c:	00090513          	addi	a0,s2,0
   11430:	00e7a223          	sw	a4,4(a5)
   11434:	79c000ef          	jal	ra,11bd0 <__malloc_unlock>
   11438:	02c12083          	lw	ra,44(sp)
   1143c:	00840513          	addi	a0,s0,8
   11440:	02812403          	lw	s0,40(sp)
   11444:	02412483          	lw	s1,36(sp)
   11448:	02012903          	lw	s2,32(sp)
   1144c:	01c12983          	lw	s3,28(sp)
   11450:	03010113          	addi	sp,sp,48
   11454:	00008067          	jalr	zero,0(ra)
   11458:	ff87f493          	andi	s1,a5,-8
   1145c:	1807c663          	blt	a5,zero,115e8 <_malloc_r+0x234>
   11460:	18b4e463          	bltu	s1,a1,115e8 <_malloc_r+0x234>
   11464:	764000ef          	jal	ra,11bc8 <__malloc_lock>
   11468:	1f700793          	addi	a5,zero,503
   1146c:	5097f263          	bgeu	a5,s1,11970 <_malloc_r+0x5bc>
   11470:	0094d793          	srli	a5,s1,0x9
   11474:	18078e63          	beq	a5,zero,11610 <_malloc_r+0x25c>
   11478:	00400713          	addi	a4,zero,4
   1147c:	44f76863          	bltu	a4,a5,118cc <_malloc_r+0x518>
   11480:	0064d793          	srli	a5,s1,0x6
   11484:	03978593          	addi	a1,a5,57
   11488:	03878813          	addi	a6,a5,56
   1148c:	00359613          	slli	a2,a1,0x3
   11490:	00002997          	auipc	s3,0x2
   11494:	04098993          	addi	s3,s3,64 # 134d0 <__malloc_av_>
   11498:	00c98633          	add	a2,s3,a2
   1149c:	00462403          	lw	s0,4(a2)
   114a0:	ff860613          	addi	a2,a2,-8
   114a4:	02860863          	beq	a2,s0,114d4 <_malloc_r+0x120>
   114a8:	00f00513          	addi	a0,zero,15
   114ac:	0140006f          	jal	zero,114c0 <_malloc_r+0x10c>
   114b0:	00c42683          	lw	a3,12(s0)
   114b4:	36075263          	bge	a4,zero,11818 <_malloc_r+0x464>
   114b8:	00d60e63          	beq	a2,a3,114d4 <_malloc_r+0x120>
   114bc:	00068413          	addi	s0,a3,0
   114c0:	00442783          	lw	a5,4(s0)
   114c4:	ffc7f793          	andi	a5,a5,-4
   114c8:	40978733          	sub	a4,a5,s1
   114cc:	fee552e3          	bge	a0,a4,114b0 <_malloc_r+0xfc>
   114d0:	00080593          	addi	a1,a6,0
   114d4:	0109a403          	lw	s0,16(s3)
   114d8:	00002897          	auipc	a7,0x2
   114dc:	00088893          	addi	a7,a7,0 # 134d8 <__malloc_av_+0x8>
   114e0:	2b140c63          	beq	s0,a7,11798 <_malloc_r+0x3e4>
   114e4:	00442783          	lw	a5,4(s0)
   114e8:	00f00693          	addi	a3,zero,15
   114ec:	ffc7f793          	andi	a5,a5,-4
   114f0:	40978733          	sub	a4,a5,s1
   114f4:	48e6c463          	blt	a3,a4,1197c <_malloc_r+0x5c8>
   114f8:	0119aa23          	sw	a7,20(s3)
   114fc:	0119a823          	sw	a7,16(s3)
   11500:	44075863          	bge	a4,zero,11950 <_malloc_r+0x59c>
   11504:	1ff00713          	addi	a4,zero,511
   11508:	0049a503          	lw	a0,4(s3)
   1150c:	36f76063          	bltu	a4,a5,1186c <_malloc_r+0x4b8>
   11510:	ff87f713          	andi	a4,a5,-8
   11514:	00870713          	addi	a4,a4,8
   11518:	00e98733          	add	a4,s3,a4
   1151c:	00072683          	lw	a3,0(a4)
   11520:	0057d613          	srli	a2,a5,0x5
   11524:	00100793          	addi	a5,zero,1
   11528:	00c797b3          	sll	a5,a5,a2
   1152c:	00f56533          	or	a0,a0,a5
   11530:	ff870793          	addi	a5,a4,-8
   11534:	00d42423          	sw	a3,8(s0)
   11538:	00f42623          	sw	a5,12(s0)
   1153c:	00a9a223          	sw	a0,4(s3)
   11540:	00872023          	sw	s0,0(a4)
   11544:	0086a623          	sw	s0,12(a3)
   11548:	4025d793          	srai	a5,a1,0x2
   1154c:	00100613          	addi	a2,zero,1
   11550:	00f61633          	sll	a2,a2,a5
   11554:	0cc56663          	bltu	a0,a2,11620 <_malloc_r+0x26c>
   11558:	00a677b3          	and	a5,a2,a0
   1155c:	02079463          	bne	a5,zero,11584 <_malloc_r+0x1d0>
   11560:	00161613          	slli	a2,a2,0x1
   11564:	ffc5f593          	andi	a1,a1,-4
   11568:	00a677b3          	and	a5,a2,a0
   1156c:	00458593          	addi	a1,a1,4
   11570:	00079a63          	bne	a5,zero,11584 <_malloc_r+0x1d0>
   11574:	00161613          	slli	a2,a2,0x1
   11578:	00a677b3          	and	a5,a2,a0
   1157c:	00458593          	addi	a1,a1,4
   11580:	fe078ae3          	beq	a5,zero,11574 <_malloc_r+0x1c0>
   11584:	00f00813          	addi	a6,zero,15
   11588:	00359313          	slli	t1,a1,0x3
   1158c:	00698333          	add	t1,s3,t1
   11590:	00030513          	addi	a0,t1,0
   11594:	00c52783          	lw	a5,12(a0)
   11598:	00058e13          	addi	t3,a1,0
   1159c:	34f50a63          	beq	a0,a5,118f0 <_malloc_r+0x53c>
   115a0:	0047a703          	lw	a4,4(a5)
   115a4:	00078413          	addi	s0,a5,0
   115a8:	00c7a783          	lw	a5,12(a5)
   115ac:	ffc77713          	andi	a4,a4,-4
   115b0:	409706b3          	sub	a3,a4,s1
   115b4:	34d84a63          	blt	a6,a3,11908 <_malloc_r+0x554>
   115b8:	fe06c2e3          	blt	a3,zero,1159c <_malloc_r+0x1e8>
   115bc:	00e40733          	add	a4,s0,a4
   115c0:	00472683          	lw	a3,4(a4)
   115c4:	00842603          	lw	a2,8(s0)
   115c8:	00090513          	addi	a0,s2,0
   115cc:	0016e693          	ori	a3,a3,1
   115d0:	00d72223          	sw	a3,4(a4)
   115d4:	00f62623          	sw	a5,12(a2)
   115d8:	00c7a423          	sw	a2,8(a5)
   115dc:	5f4000ef          	jal	ra,11bd0 <__malloc_unlock>
   115e0:	00840513          	addi	a0,s0,8
   115e4:	0100006f          	jal	zero,115f4 <_malloc_r+0x240>
   115e8:	00c00793          	addi	a5,zero,12
   115ec:	00f92023          	sw	a5,0(s2)
   115f0:	00000513          	addi	a0,zero,0
   115f4:	02c12083          	lw	ra,44(sp)
   115f8:	02812403          	lw	s0,40(sp)
   115fc:	02412483          	lw	s1,36(sp)
   11600:	02012903          	lw	s2,32(sp)
   11604:	01c12983          	lw	s3,28(sp)
   11608:	03010113          	addi	sp,sp,48
   1160c:	00008067          	jalr	zero,0(ra)
   11610:	20000613          	addi	a2,zero,512
   11614:	04000593          	addi	a1,zero,64
   11618:	03f00813          	addi	a6,zero,63
   1161c:	e75ff06f          	jal	zero,11490 <_malloc_r+0xdc>
   11620:	0089a403          	lw	s0,8(s3)
   11624:	01612823          	sw	s6,16(sp)
   11628:	00442783          	lw	a5,4(s0)
   1162c:	ffc7fb13          	andi	s6,a5,-4
   11630:	009b6863          	bltu	s6,s1,11640 <_malloc_r+0x28c>
   11634:	409b0733          	sub	a4,s6,s1
   11638:	00f00793          	addi	a5,zero,15
   1163c:	18e7cc63          	blt	a5,a4,117d4 <_malloc_r+0x420>
   11640:	01912223          	sw	s9,4(sp)
   11644:	d4418c93          	addi	s9,gp,-700 # 138e4 <__malloc_sbrk_base>
   11648:	01512a23          	sw	s5,20(sp)
   1164c:	000ca703          	lw	a4,0(s9)
   11650:	d841aa83          	lw	s5,-636(gp) # 13924 <__malloc_top_pad>
   11654:	01412c23          	sw	s4,24(sp)
   11658:	01712623          	sw	s7,12(sp)
   1165c:	fff00793          	addi	a5,zero,-1
   11660:	01640a33          	add	s4,s0,s6
   11664:	01548ab3          	add	s5,s1,s5
   11668:	3ef70063          	beq	a4,a5,11a48 <_malloc_r+0x694>
   1166c:	000017b7          	lui	a5,0x1
   11670:	00f78793          	addi	a5,a5,15 # 100f <exit-0xf0a5>
   11674:	00fa8ab3          	add	s5,s5,a5
   11678:	fffff7b7          	lui	a5,0xfffff
   1167c:	00fafab3          	and	s5,s5,a5
   11680:	000a8593          	addi	a1,s5,0
   11684:	00090513          	addi	a0,s2,0
   11688:	2d1000ef          	jal	ra,12158 <_sbrk_r>
   1168c:	fff00793          	addi	a5,zero,-1
   11690:	00050b93          	addi	s7,a0,0
   11694:	46f50c63          	beq	a0,a5,11b0c <_malloc_r+0x758>
   11698:	01812423          	sw	s8,8(sp)
   1169c:	11456263          	bltu	a0,s4,117a0 <_malloc_r+0x3ec>
   116a0:	06c18c13          	addi	s8,gp,108 # 13c0c <__malloc_current_mallinfo>
   116a4:	000c2583          	lw	a1,0(s8)
   116a8:	00ba85b3          	add	a1,s5,a1
   116ac:	00bc2023          	sw	a1,0(s8)
   116b0:	00058713          	addi	a4,a1,0
   116b4:	46aa0263          	beq	s4,a0,11b18 <_malloc_r+0x764>
   116b8:	000ca683          	lw	a3,0(s9)
   116bc:	fff00793          	addi	a5,zero,-1
   116c0:	46f68a63          	beq	a3,a5,11b34 <_malloc_r+0x780>
   116c4:	414b87b3          	sub	a5,s7,s4
   116c8:	00e787b3          	add	a5,a5,a4
   116cc:	00fc2023          	sw	a5,0(s8)
   116d0:	007bfc93          	andi	s9,s7,7
   116d4:	380c8a63          	beq	s9,zero,11a68 <_malloc_r+0x6b4>
   116d8:	419b8bb3          	sub	s7,s7,s9
   116dc:	000015b7          	lui	a1,0x1
   116e0:	008b8b93          	addi	s7,s7,8
   116e4:	00858593          	addi	a1,a1,8 # 1008 <exit-0xf0ac>
   116e8:	015b8ab3          	add	s5,s7,s5
   116ec:	419585b3          	sub	a1,a1,s9
   116f0:	415585b3          	sub	a1,a1,s5
   116f4:	01459593          	slli	a1,a1,0x14
   116f8:	0145da13          	srli	s4,a1,0x14
   116fc:	000a0593          	addi	a1,s4,0
   11700:	00090513          	addi	a0,s2,0
   11704:	255000ef          	jal	ra,12158 <_sbrk_r>
   11708:	fff00793          	addi	a5,zero,-1
   1170c:	46f50463          	beq	a0,a5,11b74 <_malloc_r+0x7c0>
   11710:	41750533          	sub	a0,a0,s7
   11714:	01450ab3          	add	s5,a0,s4
   11718:	000c2703          	lw	a4,0(s8)
   1171c:	0179a423          	sw	s7,8(s3)
   11720:	001ae793          	ori	a5,s5,1
   11724:	00ea05b3          	add	a1,s4,a4
   11728:	00fba223          	sw	a5,4(s7)
   1172c:	00bc2023          	sw	a1,0(s8)
   11730:	03340e63          	beq	s0,s3,1176c <_malloc_r+0x3b8>
   11734:	00f00693          	addi	a3,zero,15
   11738:	3566fe63          	bgeu	a3,s6,11a94 <_malloc_r+0x6e0>
   1173c:	00442703          	lw	a4,4(s0)
   11740:	ff4b0793          	addi	a5,s6,-12
   11744:	ff87f793          	andi	a5,a5,-8
   11748:	00177713          	andi	a4,a4,1
   1174c:	00f76733          	or	a4,a4,a5
   11750:	00e42223          	sw	a4,4(s0)
   11754:	00500613          	addi	a2,zero,5
   11758:	00f40733          	add	a4,s0,a5
   1175c:	00c72223          	sw	a2,4(a4)
   11760:	00c72423          	sw	a2,8(a4)
   11764:	2cf6e663          	bltu	a3,a5,11a30 <_malloc_r+0x67c>
   11768:	004ba783          	lw	a5,4(s7)
   1176c:	d8018713          	addi	a4,gp,-640 # 13920 <__malloc_max_sbrked_mem>
   11770:	00072683          	lw	a3,0(a4)
   11774:	00b6f463          	bgeu	a3,a1,1177c <_malloc_r+0x3c8>
   11778:	00b72023          	sw	a1,0(a4)
   1177c:	d7c18713          	addi	a4,gp,-644 # 1391c <__malloc_max_total_mem>
   11780:	00072683          	lw	a3,0(a4)
   11784:	00b6f463          	bgeu	a3,a1,1178c <_malloc_r+0x3d8>
   11788:	00b72023          	sw	a1,0(a4)
   1178c:	00812c03          	lw	s8,8(sp)
   11790:	000b8413          	addi	s0,s7,0
   11794:	01c0006f          	jal	zero,117b0 <_malloc_r+0x3fc>
   11798:	0049a503          	lw	a0,4(s3)
   1179c:	dadff06f          	jal	zero,11548 <_malloc_r+0x194>
   117a0:	35340c63          	beq	s0,s3,11af8 <_malloc_r+0x744>
   117a4:	0089a403          	lw	s0,8(s3)
   117a8:	00812c03          	lw	s8,8(sp)
   117ac:	00442783          	lw	a5,4(s0)
   117b0:	ffc7f793          	andi	a5,a5,-4
   117b4:	40978733          	sub	a4,a5,s1
   117b8:	2e97e463          	bltu	a5,s1,11aa0 <_malloc_r+0x6ec>
   117bc:	00f00793          	addi	a5,zero,15
   117c0:	2ee7d063          	bge	a5,a4,11aa0 <_malloc_r+0x6ec>
   117c4:	01812a03          	lw	s4,24(sp)
   117c8:	01412a83          	lw	s5,20(sp)
   117cc:	00c12b83          	lw	s7,12(sp)
   117d0:	00412c83          	lw	s9,4(sp)
   117d4:	0014e793          	ori	a5,s1,1
   117d8:	00f42223          	sw	a5,4(s0)
   117dc:	009404b3          	add	s1,s0,s1
   117e0:	0099a423          	sw	s1,8(s3)
   117e4:	00176713          	ori	a4,a4,1
   117e8:	00090513          	addi	a0,s2,0
   117ec:	00e4a223          	sw	a4,4(s1)
   117f0:	3e0000ef          	jal	ra,11bd0 <__malloc_unlock>
   117f4:	02c12083          	lw	ra,44(sp)
   117f8:	00840513          	addi	a0,s0,8
   117fc:	02812403          	lw	s0,40(sp)
   11800:	01012b03          	lw	s6,16(sp)
   11804:	02412483          	lw	s1,36(sp)
   11808:	02012903          	lw	s2,32(sp)
   1180c:	01c12983          	lw	s3,28(sp)
   11810:	03010113          	addi	sp,sp,48
   11814:	00008067          	jalr	zero,0(ra)
   11818:	00842603          	lw	a2,8(s0)
   1181c:	00f407b3          	add	a5,s0,a5
   11820:	0047a703          	lw	a4,4(a5) # fffff004 <__BSS_END__+0xfffeb3d0>
   11824:	00d62623          	sw	a3,12(a2)
   11828:	00c6a423          	sw	a2,8(a3)
   1182c:	00176713          	ori	a4,a4,1
   11830:	00090513          	addi	a0,s2,0
   11834:	00e7a223          	sw	a4,4(a5)
   11838:	398000ef          	jal	ra,11bd0 <__malloc_unlock>
   1183c:	02c12083          	lw	ra,44(sp)
   11840:	00840513          	addi	a0,s0,8
   11844:	02812403          	lw	s0,40(sp)
   11848:	02412483          	lw	s1,36(sp)
   1184c:	02012903          	lw	s2,32(sp)
   11850:	01c12983          	lw	s3,28(sp)
   11854:	03010113          	addi	sp,sp,48
   11858:	00008067          	jalr	zero,0(ra)
   1185c:	00c7a403          	lw	s0,12(a5)
   11860:	00258593          	addi	a1,a1,2
   11864:	c68788e3          	beq	a5,s0,114d4 <_malloc_r+0x120>
   11868:	ba1ff06f          	jal	zero,11408 <_malloc_r+0x54>
   1186c:	0097d713          	srli	a4,a5,0x9
   11870:	00400693          	addi	a3,zero,4
   11874:	14e6f263          	bgeu	a3,a4,119b8 <_malloc_r+0x604>
   11878:	01400693          	addi	a3,zero,20
   1187c:	24e6e263          	bltu	a3,a4,11ac0 <_malloc_r+0x70c>
   11880:	05c70613          	addi	a2,a4,92
   11884:	00361613          	slli	a2,a2,0x3
   11888:	05b70693          	addi	a3,a4,91
   1188c:	00c98633          	add	a2,s3,a2
   11890:	00062703          	lw	a4,0(a2)
   11894:	ff860613          	addi	a2,a2,-8
   11898:	00e61863          	bne	a2,a4,118a8 <_malloc_r+0x4f4>
   1189c:	1b40006f          	jal	zero,11a50 <_malloc_r+0x69c>
   118a0:	00872703          	lw	a4,8(a4)
   118a4:	00e60863          	beq	a2,a4,118b4 <_malloc_r+0x500>
   118a8:	00472683          	lw	a3,4(a4)
   118ac:	ffc6f693          	andi	a3,a3,-4
   118b0:	fed7e8e3          	bltu	a5,a3,118a0 <_malloc_r+0x4ec>
   118b4:	00c72603          	lw	a2,12(a4)
   118b8:	00c42623          	sw	a2,12(s0)
   118bc:	00e42423          	sw	a4,8(s0)
   118c0:	00862423          	sw	s0,8(a2)
   118c4:	00872623          	sw	s0,12(a4)
   118c8:	c81ff06f          	jal	zero,11548 <_malloc_r+0x194>
   118cc:	01400713          	addi	a4,zero,20
   118d0:	0ef77e63          	bgeu	a4,a5,119cc <_malloc_r+0x618>
   118d4:	05400713          	addi	a4,zero,84
   118d8:	20f76263          	bltu	a4,a5,11adc <_malloc_r+0x728>
   118dc:	00c4d793          	srli	a5,s1,0xc
   118e0:	06f78593          	addi	a1,a5,111
   118e4:	06e78813          	addi	a6,a5,110
   118e8:	00359613          	slli	a2,a1,0x3
   118ec:	ba5ff06f          	jal	zero,11490 <_malloc_r+0xdc>
   118f0:	001e0e13          	addi	t3,t3,1
   118f4:	003e7793          	andi	a5,t3,3
   118f8:	00850513          	addi	a0,a0,8
   118fc:	0e078663          	beq	a5,zero,119e8 <_malloc_r+0x634>
   11900:	00c52783          	lw	a5,12(a0)
   11904:	c99ff06f          	jal	zero,1159c <_malloc_r+0x1e8>
   11908:	00842603          	lw	a2,8(s0)
   1190c:	0014e593          	ori	a1,s1,1
   11910:	00b42223          	sw	a1,4(s0)
   11914:	00f62623          	sw	a5,12(a2)
   11918:	00c7a423          	sw	a2,8(a5)
   1191c:	009404b3          	add	s1,s0,s1
   11920:	0099aa23          	sw	s1,20(s3)
   11924:	0099a823          	sw	s1,16(s3)
   11928:	0016e793          	ori	a5,a3,1
   1192c:	00e40733          	add	a4,s0,a4
   11930:	0114a623          	sw	a7,12(s1)
   11934:	0114a423          	sw	a7,8(s1)
   11938:	00f4a223          	sw	a5,4(s1)
   1193c:	00090513          	addi	a0,s2,0
   11940:	00d72023          	sw	a3,0(a4)
   11944:	28c000ef          	jal	ra,11bd0 <__malloc_unlock>
   11948:	00840513          	addi	a0,s0,8
   1194c:	ca9ff06f          	jal	zero,115f4 <_malloc_r+0x240>
   11950:	00f407b3          	add	a5,s0,a5
   11954:	0047a703          	lw	a4,4(a5)
   11958:	00090513          	addi	a0,s2,0
   1195c:	00176713          	ori	a4,a4,1
   11960:	00e7a223          	sw	a4,4(a5)
   11964:	26c000ef          	jal	ra,11bd0 <__malloc_unlock>
   11968:	00840513          	addi	a0,s0,8
   1196c:	c89ff06f          	jal	zero,115f4 <_malloc_r+0x240>
   11970:	0034d593          	srli	a1,s1,0x3
   11974:	00848793          	addi	a5,s1,8
   11978:	a79ff06f          	jal	zero,113f0 <_malloc_r+0x3c>
   1197c:	0014e693          	ori	a3,s1,1
   11980:	00d42223          	sw	a3,4(s0)
   11984:	009404b3          	add	s1,s0,s1
   11988:	0099aa23          	sw	s1,20(s3)
   1198c:	0099a823          	sw	s1,16(s3)
   11990:	00176693          	ori	a3,a4,1
   11994:	00f407b3          	add	a5,s0,a5
   11998:	0114a623          	sw	a7,12(s1)
   1199c:	0114a423          	sw	a7,8(s1)
   119a0:	00d4a223          	sw	a3,4(s1)
   119a4:	00090513          	addi	a0,s2,0
   119a8:	00e7a023          	sw	a4,0(a5)
   119ac:	224000ef          	jal	ra,11bd0 <__malloc_unlock>
   119b0:	00840513          	addi	a0,s0,8
   119b4:	c41ff06f          	jal	zero,115f4 <_malloc_r+0x240>
   119b8:	0067d713          	srli	a4,a5,0x6
   119bc:	03970613          	addi	a2,a4,57
   119c0:	00361613          	slli	a2,a2,0x3
   119c4:	03870693          	addi	a3,a4,56
   119c8:	ec5ff06f          	jal	zero,1188c <_malloc_r+0x4d8>
   119cc:	05c78593          	addi	a1,a5,92
   119d0:	05b78813          	addi	a6,a5,91
   119d4:	00359613          	slli	a2,a1,0x3
   119d8:	ab9ff06f          	jal	zero,11490 <_malloc_r+0xdc>
   119dc:	00832783          	lw	a5,8(t1)
   119e0:	fff58593          	addi	a1,a1,-1
   119e4:	1c679e63          	bne	a5,t1,11bc0 <_malloc_r+0x80c>
   119e8:	0035f793          	andi	a5,a1,3
   119ec:	ff830313          	addi	t1,t1,-8
   119f0:	fe0796e3          	bne	a5,zero,119dc <_malloc_r+0x628>
   119f4:	0049a703          	lw	a4,4(s3)
   119f8:	fff64793          	xori	a5,a2,-1
   119fc:	00e7f7b3          	and	a5,a5,a4
   11a00:	00f9a223          	sw	a5,4(s3)
   11a04:	00161613          	slli	a2,a2,0x1
   11a08:	c0c7ece3          	bltu	a5,a2,11620 <_malloc_r+0x26c>
   11a0c:	c0060ae3          	beq	a2,zero,11620 <_malloc_r+0x26c>
   11a10:	00f67733          	and	a4,a2,a5
   11a14:	00071a63          	bne	a4,zero,11a28 <_malloc_r+0x674>
   11a18:	00161613          	slli	a2,a2,0x1
   11a1c:	00f67733          	and	a4,a2,a5
   11a20:	004e0e13          	addi	t3,t3,4
   11a24:	fe070ae3          	beq	a4,zero,11a18 <_malloc_r+0x664>
   11a28:	000e0593          	addi	a1,t3,0
   11a2c:	b5dff06f          	jal	zero,11588 <_malloc_r+0x1d4>
   11a30:	00840593          	addi	a1,s0,8
   11a34:	00090513          	addi	a0,s2,0
   11a38:	e8cff0ef          	jal	ra,110c4 <_free_r>
   11a3c:	000c2583          	lw	a1,0(s8)
   11a40:	0089ab83          	lw	s7,8(s3)
   11a44:	d25ff06f          	jal	zero,11768 <_malloc_r+0x3b4>
   11a48:	010a8a93          	addi	s5,s5,16
   11a4c:	c35ff06f          	jal	zero,11680 <_malloc_r+0x2cc>
   11a50:	4026d693          	srai	a3,a3,0x2
   11a54:	00100793          	addi	a5,zero,1
   11a58:	00d797b3          	sll	a5,a5,a3
   11a5c:	00f56533          	or	a0,a0,a5
   11a60:	00a9a223          	sw	a0,4(s3)
   11a64:	e55ff06f          	jal	zero,118b8 <_malloc_r+0x504>
   11a68:	015b85b3          	add	a1,s7,s5
   11a6c:	40b005b3          	sub	a1,zero,a1
   11a70:	01459593          	slli	a1,a1,0x14
   11a74:	0145da13          	srli	s4,a1,0x14
   11a78:	000a0593          	addi	a1,s4,0
   11a7c:	00090513          	addi	a0,s2,0
   11a80:	6d8000ef          	jal	ra,12158 <_sbrk_r>
   11a84:	fff00793          	addi	a5,zero,-1
   11a88:	c8f514e3          	bne	a0,a5,11710 <_malloc_r+0x35c>
   11a8c:	00000a13          	addi	s4,zero,0
   11a90:	c89ff06f          	jal	zero,11718 <_malloc_r+0x364>
   11a94:	00812c03          	lw	s8,8(sp)
   11a98:	00100793          	addi	a5,zero,1
   11a9c:	00fba223          	sw	a5,4(s7)
   11aa0:	00090513          	addi	a0,s2,0
   11aa4:	12c000ef          	jal	ra,11bd0 <__malloc_unlock>
   11aa8:	01812a03          	lw	s4,24(sp)
   11aac:	01412a83          	lw	s5,20(sp)
   11ab0:	01012b03          	lw	s6,16(sp)
   11ab4:	00c12b83          	lw	s7,12(sp)
   11ab8:	00412c83          	lw	s9,4(sp)
   11abc:	b35ff06f          	jal	zero,115f0 <_malloc_r+0x23c>
   11ac0:	05400693          	addi	a3,zero,84
   11ac4:	06e6ec63          	bltu	a3,a4,11b3c <_malloc_r+0x788>
   11ac8:	00c7d713          	srli	a4,a5,0xc
   11acc:	06f70613          	addi	a2,a4,111
   11ad0:	00361613          	slli	a2,a2,0x3
   11ad4:	06e70693          	addi	a3,a4,110
   11ad8:	db5ff06f          	jal	zero,1188c <_malloc_r+0x4d8>
   11adc:	15400713          	addi	a4,zero,340
   11ae0:	06f76c63          	bltu	a4,a5,11b58 <_malloc_r+0x7a4>
   11ae4:	00f4d793          	srli	a5,s1,0xf
   11ae8:	07878593          	addi	a1,a5,120
   11aec:	07778813          	addi	a6,a5,119
   11af0:	00359613          	slli	a2,a1,0x3
   11af4:	99dff06f          	jal	zero,11490 <_malloc_r+0xdc>
   11af8:	06c18c13          	addi	s8,gp,108 # 13c0c <__malloc_current_mallinfo>
   11afc:	000c2703          	lw	a4,0(s8)
   11b00:	00ea8733          	add	a4,s5,a4
   11b04:	00ec2023          	sw	a4,0(s8)
   11b08:	bb1ff06f          	jal	zero,116b8 <_malloc_r+0x304>
   11b0c:	0089a403          	lw	s0,8(s3)
   11b10:	00442783          	lw	a5,4(s0)
   11b14:	c9dff06f          	jal	zero,117b0 <_malloc_r+0x3fc>
   11b18:	01451793          	slli	a5,a0,0x14
   11b1c:	b8079ee3          	bne	a5,zero,116b8 <_malloc_r+0x304>
   11b20:	0089ab83          	lw	s7,8(s3)
   11b24:	015b07b3          	add	a5,s6,s5
   11b28:	0017e793          	ori	a5,a5,1
   11b2c:	00fba223          	sw	a5,4(s7)
   11b30:	c3dff06f          	jal	zero,1176c <_malloc_r+0x3b8>
   11b34:	017ca023          	sw	s7,0(s9)
   11b38:	b99ff06f          	jal	zero,116d0 <_malloc_r+0x31c>
   11b3c:	15400693          	addi	a3,zero,340
   11b40:	04e6e463          	bltu	a3,a4,11b88 <_malloc_r+0x7d4>
   11b44:	00f7d713          	srli	a4,a5,0xf
   11b48:	07870613          	addi	a2,a4,120
   11b4c:	00361613          	slli	a2,a2,0x3
   11b50:	07770693          	addi	a3,a4,119
   11b54:	d39ff06f          	jal	zero,1188c <_malloc_r+0x4d8>
   11b58:	55400713          	addi	a4,zero,1364
   11b5c:	04f76463          	bltu	a4,a5,11ba4 <_malloc_r+0x7f0>
   11b60:	0124d793          	srli	a5,s1,0x12
   11b64:	07d78593          	addi	a1,a5,125
   11b68:	07c78813          	addi	a6,a5,124
   11b6c:	00359613          	slli	a2,a1,0x3
   11b70:	921ff06f          	jal	zero,11490 <_malloc_r+0xdc>
   11b74:	ff8c8c93          	addi	s9,s9,-8
   11b78:	019a8ab3          	add	s5,s5,s9
   11b7c:	417a8ab3          	sub	s5,s5,s7
   11b80:	00000a13          	addi	s4,zero,0
   11b84:	b95ff06f          	jal	zero,11718 <_malloc_r+0x364>
   11b88:	55400693          	addi	a3,zero,1364
   11b8c:	02e6e463          	bltu	a3,a4,11bb4 <_malloc_r+0x800>
   11b90:	0127d713          	srli	a4,a5,0x12
   11b94:	07d70613          	addi	a2,a4,125
   11b98:	00361613          	slli	a2,a2,0x3
   11b9c:	07c70693          	addi	a3,a4,124
   11ba0:	cedff06f          	jal	zero,1188c <_malloc_r+0x4d8>
   11ba4:	3f800613          	addi	a2,zero,1016
   11ba8:	07f00593          	addi	a1,zero,127
   11bac:	07e00813          	addi	a6,zero,126
   11bb0:	8e1ff06f          	jal	zero,11490 <_malloc_r+0xdc>
   11bb4:	3f800613          	addi	a2,zero,1016
   11bb8:	07e00693          	addi	a3,zero,126
   11bbc:	cd1ff06f          	jal	zero,1188c <_malloc_r+0x4d8>
   11bc0:	0049a783          	lw	a5,4(s3)
   11bc4:	e41ff06f          	jal	zero,11a04 <_malloc_r+0x650>

00011bc8 <__malloc_lock>:
   11bc8:	d6818513          	addi	a0,gp,-664 # 13908 <__lock___malloc_recursive_mutex>
   11bcc:	894ff06f          	jal	zero,10c60 <__retarget_lock_acquire_recursive>

00011bd0 <__malloc_unlock>:
   11bd0:	d6818513          	addi	a0,gp,-664 # 13908 <__lock___malloc_recursive_mutex>
   11bd4:	8a4ff06f          	jal	zero,10c78 <__retarget_lock_release_recursive>

00011bd8 <_fclose_r>:
   11bd8:	ff010113          	addi	sp,sp,-16
   11bdc:	00112623          	sw	ra,12(sp)
   11be0:	01212023          	sw	s2,0(sp)
   11be4:	0e058263          	beq	a1,zero,11cc8 <_fclose_r+0xf0>
   11be8:	00812423          	sw	s0,8(sp)
   11bec:	00912223          	sw	s1,4(sp)
   11bf0:	00058413          	addi	s0,a1,0
   11bf4:	00050493          	addi	s1,a0,0
   11bf8:	00050663          	beq	a0,zero,11c04 <_fclose_r+0x2c>
   11bfc:	03452783          	lw	a5,52(a0)
   11c00:	10078063          	beq	a5,zero,11d00 <_fclose_r+0x128>
   11c04:	06442783          	lw	a5,100(s0)
   11c08:	00c41703          	lh	a4,12(s0)
   11c0c:	0017f793          	andi	a5,a5,1
   11c10:	0a079663          	bne	a5,zero,11cbc <_fclose_r+0xe4>
   11c14:	20077713          	andi	a4,a4,512
   11c18:	0e070863          	beq	a4,zero,11d08 <_fclose_r+0x130>
   11c1c:	00040593          	addi	a1,s0,0
   11c20:	00048513          	addi	a0,s1,0
   11c24:	12c000ef          	jal	ra,11d50 <__sflush_r>
   11c28:	02c42783          	lw	a5,44(s0)
   11c2c:	00050913          	addi	s2,a0,0
   11c30:	00078a63          	beq	a5,zero,11c44 <_fclose_r+0x6c>
   11c34:	01c42583          	lw	a1,28(s0)
   11c38:	00048513          	addi	a0,s1,0
   11c3c:	000780e7          	jalr	ra,0(a5)
   11c40:	0a054063          	blt	a0,zero,11ce0 <_fclose_r+0x108>
   11c44:	00c45783          	lhu	a5,12(s0)
   11c48:	0807f793          	andi	a5,a5,128
   11c4c:	0a079263          	bne	a5,zero,11cf0 <_fclose_r+0x118>
   11c50:	03042583          	lw	a1,48(s0)
   11c54:	00058c63          	beq	a1,zero,11c6c <_fclose_r+0x94>
   11c58:	04040793          	addi	a5,s0,64
   11c5c:	00f58663          	beq	a1,a5,11c68 <_fclose_r+0x90>
   11c60:	00048513          	addi	a0,s1,0
   11c64:	c60ff0ef          	jal	ra,110c4 <_free_r>
   11c68:	02042823          	sw	zero,48(s0)
   11c6c:	04442583          	lw	a1,68(s0)
   11c70:	00058863          	beq	a1,zero,11c80 <_fclose_r+0xa8>
   11c74:	00048513          	addi	a0,s1,0
   11c78:	c4cff0ef          	jal	ra,110c4 <_free_r>
   11c7c:	04042223          	sw	zero,68(s0)
   11c80:	999fe0ef          	jal	ra,10618 <__sfp_lock_acquire>
   11c84:	06442783          	lw	a5,100(s0)
   11c88:	00041623          	sh	zero,12(s0)
   11c8c:	0017f793          	andi	a5,a5,1
   11c90:	0a078463          	beq	a5,zero,11d38 <_fclose_r+0x160>
   11c94:	05842503          	lw	a0,88(s0)
   11c98:	fc1fe0ef          	jal	ra,10c58 <__retarget_lock_close_recursive>
   11c9c:	985fe0ef          	jal	ra,10620 <__sfp_lock_release>
   11ca0:	00c12083          	lw	ra,12(sp)
   11ca4:	00812403          	lw	s0,8(sp)
   11ca8:	00412483          	lw	s1,4(sp)
   11cac:	00090513          	addi	a0,s2,0
   11cb0:	00012903          	lw	s2,0(sp)
   11cb4:	01010113          	addi	sp,sp,16
   11cb8:	00008067          	jalr	zero,0(ra)
   11cbc:	f60710e3          	bne	a4,zero,11c1c <_fclose_r+0x44>
   11cc0:	00812403          	lw	s0,8(sp)
   11cc4:	00412483          	lw	s1,4(sp)
   11cc8:	00c12083          	lw	ra,12(sp)
   11ccc:	00000913          	addi	s2,zero,0
   11cd0:	00090513          	addi	a0,s2,0
   11cd4:	00012903          	lw	s2,0(sp)
   11cd8:	01010113          	addi	sp,sp,16
   11cdc:	00008067          	jalr	zero,0(ra)
   11ce0:	00c45783          	lhu	a5,12(s0)
   11ce4:	fff00913          	addi	s2,zero,-1
   11ce8:	0807f793          	andi	a5,a5,128
   11cec:	f60782e3          	beq	a5,zero,11c50 <_fclose_r+0x78>
   11cf0:	01042583          	lw	a1,16(s0)
   11cf4:	00048513          	addi	a0,s1,0
   11cf8:	bccff0ef          	jal	ra,110c4 <_free_r>
   11cfc:	f55ff06f          	jal	zero,11c50 <_fclose_r+0x78>
   11d00:	8b9fe0ef          	jal	ra,105b8 <__sinit>
   11d04:	f01ff06f          	jal	zero,11c04 <_fclose_r+0x2c>
   11d08:	05842503          	lw	a0,88(s0)
   11d0c:	f55fe0ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   11d10:	00c41783          	lh	a5,12(s0)
   11d14:	f00794e3          	bne	a5,zero,11c1c <_fclose_r+0x44>
   11d18:	06442783          	lw	a5,100(s0)
   11d1c:	0017f793          	andi	a5,a5,1
   11d20:	fa0790e3          	bne	a5,zero,11cc0 <_fclose_r+0xe8>
   11d24:	05842503          	lw	a0,88(s0)
   11d28:	f51fe0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   11d2c:	00812403          	lw	s0,8(sp)
   11d30:	00412483          	lw	s1,4(sp)
   11d34:	f95ff06f          	jal	zero,11cc8 <_fclose_r+0xf0>
   11d38:	05842503          	lw	a0,88(s0)
   11d3c:	f3dfe0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   11d40:	f55ff06f          	jal	zero,11c94 <_fclose_r+0xbc>

00011d44 <fclose>:
   11d44:	00050593          	addi	a1,a0,0
   11d48:	d3c1a503          	lw	a0,-708(gp) # 138dc <_impure_ptr>
   11d4c:	e8dff06f          	jal	zero,11bd8 <_fclose_r>

00011d50 <__sflush_r>:
   11d50:	00c59703          	lh	a4,12(a1)
   11d54:	fe010113          	addi	sp,sp,-32
   11d58:	00812c23          	sw	s0,24(sp)
   11d5c:	01312623          	sw	s3,12(sp)
   11d60:	00112e23          	sw	ra,28(sp)
   11d64:	00877793          	andi	a5,a4,8
   11d68:	00058413          	addi	s0,a1,0
   11d6c:	00050993          	addi	s3,a0,0
   11d70:	12079063          	bne	a5,zero,11e90 <__sflush_r+0x140>
   11d74:	000017b7          	lui	a5,0x1
   11d78:	80078793          	addi	a5,a5,-2048 # 800 <exit-0xf8b4>
   11d7c:	0045a683          	lw	a3,4(a1)
   11d80:	00f767b3          	or	a5,a4,a5
   11d84:	00f59623          	sh	a5,12(a1)
   11d88:	18d05a63          	bge	zero,a3,11f1c <__sflush_r+0x1cc>
   11d8c:	02842803          	lw	a6,40(s0)
   11d90:	0e080463          	beq	a6,zero,11e78 <__sflush_r+0x128>
   11d94:	00912a23          	sw	s1,20(sp)
   11d98:	01371693          	slli	a3,a4,0x13
   11d9c:	0009a483          	lw	s1,0(s3)
   11da0:	0009a023          	sw	zero,0(s3)
   11da4:	1806c863          	blt	a3,zero,11f34 <__sflush_r+0x1e4>
   11da8:	01c42583          	lw	a1,28(s0)
   11dac:	00000613          	addi	a2,zero,0
   11db0:	00100693          	addi	a3,zero,1
   11db4:	00098513          	addi	a0,s3,0
   11db8:	000800e7          	jalr	ra,0(a6)
   11dbc:	fff00793          	addi	a5,zero,-1
   11dc0:	00050613          	addi	a2,a0,0
   11dc4:	1af50a63          	beq	a0,a5,11f78 <__sflush_r+0x228>
   11dc8:	00c41783          	lh	a5,12(s0)
   11dcc:	02842803          	lw	a6,40(s0)
   11dd0:	0047f793          	andi	a5,a5,4
   11dd4:	00078e63          	beq	a5,zero,11df0 <__sflush_r+0xa0>
   11dd8:	00442703          	lw	a4,4(s0)
   11ddc:	03042783          	lw	a5,48(s0)
   11de0:	40e60633          	sub	a2,a2,a4
   11de4:	00078663          	beq	a5,zero,11df0 <__sflush_r+0xa0>
   11de8:	03c42783          	lw	a5,60(s0)
   11dec:	40f60633          	sub	a2,a2,a5
   11df0:	01c42583          	lw	a1,28(s0)
   11df4:	00000693          	addi	a3,zero,0
   11df8:	00098513          	addi	a0,s3,0
   11dfc:	000800e7          	jalr	ra,0(a6)
   11e00:	fff00713          	addi	a4,zero,-1
   11e04:	00c41783          	lh	a5,12(s0)
   11e08:	12e51a63          	bne	a0,a4,11f3c <__sflush_r+0x1ec>
   11e0c:	0009a683          	lw	a3,0(s3)
   11e10:	01d00713          	addi	a4,zero,29
   11e14:	18d76063          	bltu	a4,a3,11f94 <__sflush_r+0x244>
   11e18:	20400737          	lui	a4,0x20400
   11e1c:	00170713          	addi	a4,a4,1 # 20400001 <__BSS_END__+0x203ec3cd>
   11e20:	00d75733          	srl	a4,a4,a3
   11e24:	00177713          	andi	a4,a4,1
   11e28:	16070663          	beq	a4,zero,11f94 <__sflush_r+0x244>
   11e2c:	01042603          	lw	a2,16(s0)
   11e30:	fffff737          	lui	a4,0xfffff
   11e34:	7ff70713          	addi	a4,a4,2047 # fffff7ff <__BSS_END__+0xfffebbcb>
   11e38:	00e7f733          	and	a4,a5,a4
   11e3c:	00e41623          	sh	a4,12(s0)
   11e40:	00042223          	sw	zero,4(s0)
   11e44:	00c42023          	sw	a2,0(s0)
   11e48:	01379713          	slli	a4,a5,0x13
   11e4c:	00075463          	bge	a4,zero,11e54 <__sflush_r+0x104>
   11e50:	10068863          	beq	a3,zero,11f60 <__sflush_r+0x210>
   11e54:	03042583          	lw	a1,48(s0)
   11e58:	0099a023          	sw	s1,0(s3)
   11e5c:	10058a63          	beq	a1,zero,11f70 <__sflush_r+0x220>
   11e60:	04040793          	addi	a5,s0,64
   11e64:	00f58663          	beq	a1,a5,11e70 <__sflush_r+0x120>
   11e68:	00098513          	addi	a0,s3,0
   11e6c:	a58ff0ef          	jal	ra,110c4 <_free_r>
   11e70:	01412483          	lw	s1,20(sp)
   11e74:	02042823          	sw	zero,48(s0)
   11e78:	01c12083          	lw	ra,28(sp)
   11e7c:	01812403          	lw	s0,24(sp)
   11e80:	00c12983          	lw	s3,12(sp)
   11e84:	00000513          	addi	a0,zero,0
   11e88:	02010113          	addi	sp,sp,32
   11e8c:	00008067          	jalr	zero,0(ra)
   11e90:	01212823          	sw	s2,16(sp)
   11e94:	0105a903          	lw	s2,16(a1)
   11e98:	08090a63          	beq	s2,zero,11f2c <__sflush_r+0x1dc>
   11e9c:	00912a23          	sw	s1,20(sp)
   11ea0:	0005a483          	lw	s1,0(a1)
   11ea4:	00377713          	andi	a4,a4,3
   11ea8:	0125a023          	sw	s2,0(a1)
   11eac:	412484b3          	sub	s1,s1,s2
   11eb0:	00000793          	addi	a5,zero,0
   11eb4:	00071463          	bne	a4,zero,11ebc <__sflush_r+0x16c>
   11eb8:	0145a783          	lw	a5,20(a1)
   11ebc:	00f42423          	sw	a5,8(s0)
   11ec0:	00904863          	blt	zero,s1,11ed0 <__sflush_r+0x180>
   11ec4:	0640006f          	jal	zero,11f28 <__sflush_r+0x1d8>
   11ec8:	00a90933          	add	s2,s2,a0
   11ecc:	04905e63          	bge	zero,s1,11f28 <__sflush_r+0x1d8>
   11ed0:	02442783          	lw	a5,36(s0)
   11ed4:	01c42583          	lw	a1,28(s0)
   11ed8:	00048693          	addi	a3,s1,0
   11edc:	00090613          	addi	a2,s2,0
   11ee0:	00098513          	addi	a0,s3,0
   11ee4:	000780e7          	jalr	ra,0(a5)
   11ee8:	40a484b3          	sub	s1,s1,a0
   11eec:	fca04ee3          	blt	zero,a0,11ec8 <__sflush_r+0x178>
   11ef0:	00c41783          	lh	a5,12(s0)
   11ef4:	01012903          	lw	s2,16(sp)
   11ef8:	0407e793          	ori	a5,a5,64
   11efc:	01c12083          	lw	ra,28(sp)
   11f00:	00f41623          	sh	a5,12(s0)
   11f04:	01812403          	lw	s0,24(sp)
   11f08:	01412483          	lw	s1,20(sp)
   11f0c:	00c12983          	lw	s3,12(sp)
   11f10:	fff00513          	addi	a0,zero,-1
   11f14:	02010113          	addi	sp,sp,32
   11f18:	00008067          	jalr	zero,0(ra)
   11f1c:	03c5a683          	lw	a3,60(a1)
   11f20:	e6d046e3          	blt	zero,a3,11d8c <__sflush_r+0x3c>
   11f24:	f55ff06f          	jal	zero,11e78 <__sflush_r+0x128>
   11f28:	01412483          	lw	s1,20(sp)
   11f2c:	01012903          	lw	s2,16(sp)
   11f30:	f49ff06f          	jal	zero,11e78 <__sflush_r+0x128>
   11f34:	05042603          	lw	a2,80(s0)
   11f38:	e99ff06f          	jal	zero,11dd0 <__sflush_r+0x80>
   11f3c:	01042683          	lw	a3,16(s0)
   11f40:	fffff737          	lui	a4,0xfffff
   11f44:	7ff70713          	addi	a4,a4,2047 # fffff7ff <__BSS_END__+0xfffebbcb>
   11f48:	00e7f733          	and	a4,a5,a4
   11f4c:	00e41623          	sh	a4,12(s0)
   11f50:	00042223          	sw	zero,4(s0)
   11f54:	00d42023          	sw	a3,0(s0)
   11f58:	01379713          	slli	a4,a5,0x13
   11f5c:	ee075ce3          	bge	a4,zero,11e54 <__sflush_r+0x104>
   11f60:	03042583          	lw	a1,48(s0)
   11f64:	04a42823          	sw	a0,80(s0)
   11f68:	0099a023          	sw	s1,0(s3)
   11f6c:	ee059ae3          	bne	a1,zero,11e60 <__sflush_r+0x110>
   11f70:	01412483          	lw	s1,20(sp)
   11f74:	f05ff06f          	jal	zero,11e78 <__sflush_r+0x128>
   11f78:	0009a783          	lw	a5,0(s3)
   11f7c:	e40786e3          	beq	a5,zero,11dc8 <__sflush_r+0x78>
   11f80:	01d00713          	addi	a4,zero,29
   11f84:	00e78c63          	beq	a5,a4,11f9c <__sflush_r+0x24c>
   11f88:	01600713          	addi	a4,zero,22
   11f8c:	00e78863          	beq	a5,a4,11f9c <__sflush_r+0x24c>
   11f90:	00c41783          	lh	a5,12(s0)
   11f94:	0407e793          	ori	a5,a5,64
   11f98:	f65ff06f          	jal	zero,11efc <__sflush_r+0x1ac>
   11f9c:	0099a023          	sw	s1,0(s3)
   11fa0:	01412483          	lw	s1,20(sp)
   11fa4:	ed5ff06f          	jal	zero,11e78 <__sflush_r+0x128>

00011fa8 <_fflush_r>:
   11fa8:	ff010113          	addi	sp,sp,-16
   11fac:	00812423          	sw	s0,8(sp)
   11fb0:	00912223          	sw	s1,4(sp)
   11fb4:	00112623          	sw	ra,12(sp)
   11fb8:	01212023          	sw	s2,0(sp)
   11fbc:	00050493          	addi	s1,a0,0
   11fc0:	00058413          	addi	s0,a1,0
   11fc4:	00050663          	beq	a0,zero,11fd0 <_fflush_r+0x28>
   11fc8:	03452783          	lw	a5,52(a0)
   11fcc:	0a078a63          	beq	a5,zero,12080 <_fflush_r+0xd8>
   11fd0:	00c41783          	lh	a5,12(s0)
   11fd4:	00000913          	addi	s2,zero,0
   11fd8:	04078063          	beq	a5,zero,12018 <_fflush_r+0x70>
   11fdc:	06442703          	lw	a4,100(s0)
   11fe0:	00177713          	andi	a4,a4,1
   11fe4:	00071663          	bne	a4,zero,11ff0 <_fflush_r+0x48>
   11fe8:	2007f793          	andi	a5,a5,512
   11fec:	04078463          	beq	a5,zero,12034 <_fflush_r+0x8c>
   11ff0:	00048513          	addi	a0,s1,0
   11ff4:	00040593          	addi	a1,s0,0
   11ff8:	d59ff0ef          	jal	ra,11d50 <__sflush_r>
   11ffc:	06442783          	lw	a5,100(s0)
   12000:	00050913          	addi	s2,a0,0
   12004:	0017f793          	andi	a5,a5,1
   12008:	00079863          	bne	a5,zero,12018 <_fflush_r+0x70>
   1200c:	00c45783          	lhu	a5,12(s0)
   12010:	2007f793          	andi	a5,a5,512
   12014:	04078463          	beq	a5,zero,1205c <_fflush_r+0xb4>
   12018:	00c12083          	lw	ra,12(sp)
   1201c:	00812403          	lw	s0,8(sp)
   12020:	00412483          	lw	s1,4(sp)
   12024:	00090513          	addi	a0,s2,0
   12028:	00012903          	lw	s2,0(sp)
   1202c:	01010113          	addi	sp,sp,16
   12030:	00008067          	jalr	zero,0(ra)
   12034:	05842503          	lw	a0,88(s0)
   12038:	c29fe0ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   1203c:	00048513          	addi	a0,s1,0
   12040:	00040593          	addi	a1,s0,0
   12044:	d0dff0ef          	jal	ra,11d50 <__sflush_r>
   12048:	06442783          	lw	a5,100(s0)
   1204c:	00050913          	addi	s2,a0,0
   12050:	0017f793          	andi	a5,a5,1
   12054:	fc0792e3          	bne	a5,zero,12018 <_fflush_r+0x70>
   12058:	fb5ff06f          	jal	zero,1200c <_fflush_r+0x64>
   1205c:	05842503          	lw	a0,88(s0)
   12060:	c19fe0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   12064:	00c12083          	lw	ra,12(sp)
   12068:	00812403          	lw	s0,8(sp)
   1206c:	00412483          	lw	s1,4(sp)
   12070:	00090513          	addi	a0,s2,0
   12074:	00012903          	lw	s2,0(sp)
   12078:	01010113          	addi	sp,sp,16
   1207c:	00008067          	jalr	zero,0(ra)
   12080:	d38fe0ef          	jal	ra,105b8 <__sinit>
   12084:	f4dff06f          	jal	zero,11fd0 <_fflush_r+0x28>

00012088 <fflush>:
   12088:	0a050a63          	beq	a0,zero,1213c <fflush+0xb4>
   1208c:	ff010113          	addi	sp,sp,-16
   12090:	01212023          	sw	s2,0(sp)
   12094:	d3c1a903          	lw	s2,-708(gp) # 138dc <_impure_ptr>
   12098:	00812423          	sw	s0,8(sp)
   1209c:	00112623          	sw	ra,12(sp)
   120a0:	00912223          	sw	s1,4(sp)
   120a4:	00050413          	addi	s0,a0,0
   120a8:	00090663          	beq	s2,zero,120b4 <fflush+0x2c>
   120ac:	03492783          	lw	a5,52(s2)
   120b0:	06078463          	beq	a5,zero,12118 <fflush+0x90>
   120b4:	00c41783          	lh	a5,12(s0)
   120b8:	00000493          	addi	s1,zero,0
   120bc:	04078063          	beq	a5,zero,120fc <fflush+0x74>
   120c0:	06442703          	lw	a4,100(s0)
   120c4:	00177713          	andi	a4,a4,1
   120c8:	00071663          	bne	a4,zero,120d4 <fflush+0x4c>
   120cc:	2007f793          	andi	a5,a5,512
   120d0:	04078a63          	beq	a5,zero,12124 <fflush+0x9c>
   120d4:	00090513          	addi	a0,s2,0
   120d8:	00040593          	addi	a1,s0,0
   120dc:	c75ff0ef          	jal	ra,11d50 <__sflush_r>
   120e0:	06442783          	lw	a5,100(s0)
   120e4:	00050493          	addi	s1,a0,0
   120e8:	0017f793          	andi	a5,a5,1
   120ec:	00079863          	bne	a5,zero,120fc <fflush+0x74>
   120f0:	00c45783          	lhu	a5,12(s0)
   120f4:	2007f793          	andi	a5,a5,512
   120f8:	02078c63          	beq	a5,zero,12130 <fflush+0xa8>
   120fc:	00c12083          	lw	ra,12(sp)
   12100:	00812403          	lw	s0,8(sp)
   12104:	00012903          	lw	s2,0(sp)
   12108:	00048513          	addi	a0,s1,0
   1210c:	00412483          	lw	s1,4(sp)
   12110:	01010113          	addi	sp,sp,16
   12114:	00008067          	jalr	zero,0(ra)
   12118:	00090513          	addi	a0,s2,0
   1211c:	c9cfe0ef          	jal	ra,105b8 <__sinit>
   12120:	f95ff06f          	jal	zero,120b4 <fflush+0x2c>
   12124:	05842503          	lw	a0,88(s0)
   12128:	b39fe0ef          	jal	ra,10c60 <__retarget_lock_acquire_recursive>
   1212c:	fa9ff06f          	jal	zero,120d4 <fflush+0x4c>
   12130:	05842503          	lw	a0,88(s0)
   12134:	b45fe0ef          	jal	ra,10c78 <__retarget_lock_release_recursive>
   12138:	fc5ff06f          	jal	zero,120fc <fflush+0x74>
   1213c:	00001617          	auipc	a2,0x1
   12140:	26460613          	addi	a2,a2,612 # 133a0 <__sglue>
   12144:	00000597          	auipc	a1,0x0
   12148:	e6458593          	addi	a1,a1,-412 # 11fa8 <_fflush_r>
   1214c:	00001517          	auipc	a0,0x1
   12150:	26450513          	addi	a0,a0,612 # 133b0 <_impure_data>
   12154:	d34fe06f          	jal	zero,10688 <_fwalk_sglue>

00012158 <_sbrk_r>:
   12158:	ff010113          	addi	sp,sp,-16
   1215c:	00812423          	sw	s0,8(sp)
   12160:	00050413          	addi	s0,a0,0
   12164:	00058513          	addi	a0,a1,0
   12168:	d401aa23          	sw	zero,-684(gp) # 138f4 <errno>
   1216c:	00112623          	sw	ra,12(sp)
   12170:	154000ef          	jal	ra,122c4 <_sbrk>
   12174:	fff00793          	addi	a5,zero,-1
   12178:	00f50a63          	beq	a0,a5,1218c <_sbrk_r+0x34>
   1217c:	00c12083          	lw	ra,12(sp)
   12180:	00812403          	lw	s0,8(sp)
   12184:	01010113          	addi	sp,sp,16
   12188:	00008067          	jalr	zero,0(ra)
   1218c:	00912223          	sw	s1,4(sp)
   12190:	d5418493          	addi	s1,gp,-684 # 138f4 <errno>
   12194:	0004a783          	lw	a5,0(s1)
   12198:	00078e63          	beq	a5,zero,121b4 <_sbrk_r+0x5c>
   1219c:	00c12083          	lw	ra,12(sp)
   121a0:	00f42023          	sw	a5,0(s0)
   121a4:	00812403          	lw	s0,8(sp)
   121a8:	00412483          	lw	s1,4(sp)
   121ac:	01010113          	addi	sp,sp,16
   121b0:	00008067          	jalr	zero,0(ra)
   121b4:	00c12083          	lw	ra,12(sp)
   121b8:	00812403          	lw	s0,8(sp)
   121bc:	00412483          	lw	s1,4(sp)
   121c0:	01010113          	addi	sp,sp,16
   121c4:	00008067          	jalr	zero,0(ra)

000121c8 <_close>:
   121c8:	ff010113          	addi	sp,sp,-16
   121cc:	00112623          	sw	ra,12(sp)
   121d0:	00812423          	sw	s0,8(sp)
   121d4:	03900893          	addi	a7,zero,57
   121d8:	00000073          	ecall
   121dc:	00050413          	addi	s0,a0,0
   121e0:	00054c63          	blt	a0,zero,121f8 <_close+0x30>
   121e4:	00c12083          	lw	ra,12(sp)
   121e8:	00040513          	addi	a0,s0,0
   121ec:	00812403          	lw	s0,8(sp)
   121f0:	01010113          	addi	sp,sp,16
   121f4:	00008067          	jalr	zero,0(ra)
   121f8:	40800433          	sub	s0,zero,s0
   121fc:	188000ef          	jal	ra,12384 <__errno>
   12200:	00852023          	sw	s0,0(a0)
   12204:	fff00413          	addi	s0,zero,-1
   12208:	fddff06f          	jal	zero,121e4 <_close+0x1c>

0001220c <_exit>:
   1220c:	05d00893          	addi	a7,zero,93
   12210:	00000073          	ecall
   12214:	00054463          	blt	a0,zero,1221c <_exit+0x10>
   12218:	0000006f          	jal	zero,12218 <_exit+0xc>
   1221c:	ff010113          	addi	sp,sp,-16
   12220:	00812423          	sw	s0,8(sp)
   12224:	00050413          	addi	s0,a0,0
   12228:	00112623          	sw	ra,12(sp)
   1222c:	40800433          	sub	s0,zero,s0
   12230:	154000ef          	jal	ra,12384 <__errno>
   12234:	00852023          	sw	s0,0(a0)
   12238:	0000006f          	jal	zero,12238 <_exit+0x2c>

0001223c <_lseek>:
   1223c:	ff010113          	addi	sp,sp,-16
   12240:	00112623          	sw	ra,12(sp)
   12244:	00812423          	sw	s0,8(sp)
   12248:	03e00893          	addi	a7,zero,62
   1224c:	00000073          	ecall
   12250:	00050413          	addi	s0,a0,0
   12254:	00054c63          	blt	a0,zero,1226c <_lseek+0x30>
   12258:	00c12083          	lw	ra,12(sp)
   1225c:	00040513          	addi	a0,s0,0
   12260:	00812403          	lw	s0,8(sp)
   12264:	01010113          	addi	sp,sp,16
   12268:	00008067          	jalr	zero,0(ra)
   1226c:	40800433          	sub	s0,zero,s0
   12270:	114000ef          	jal	ra,12384 <__errno>
   12274:	00852023          	sw	s0,0(a0)
   12278:	fff00413          	addi	s0,zero,-1
   1227c:	fddff06f          	jal	zero,12258 <_lseek+0x1c>

00012280 <_read>:
   12280:	ff010113          	addi	sp,sp,-16
   12284:	00112623          	sw	ra,12(sp)
   12288:	00812423          	sw	s0,8(sp)
   1228c:	03f00893          	addi	a7,zero,63
   12290:	00000073          	ecall
   12294:	00050413          	addi	s0,a0,0
   12298:	00054c63          	blt	a0,zero,122b0 <_read+0x30>
   1229c:	00c12083          	lw	ra,12(sp)
   122a0:	00040513          	addi	a0,s0,0
   122a4:	00812403          	lw	s0,8(sp)
   122a8:	01010113          	addi	sp,sp,16
   122ac:	00008067          	jalr	zero,0(ra)
   122b0:	40800433          	sub	s0,zero,s0
   122b4:	0d0000ef          	jal	ra,12384 <__errno>
   122b8:	00852023          	sw	s0,0(a0)
   122bc:	fff00413          	addi	s0,zero,-1
   122c0:	fddff06f          	jal	zero,1229c <_read+0x1c>

000122c4 <_sbrk>:
   122c4:	d8818693          	addi	a3,gp,-632 # 13928 <heap_end.0>
   122c8:	0006a703          	lw	a4,0(a3)
   122cc:	ff010113          	addi	sp,sp,-16
   122d0:	00112623          	sw	ra,12(sp)
   122d4:	00050793          	addi	a5,a0,0
   122d8:	02071063          	bne	a4,zero,122f8 <_sbrk+0x34>
   122dc:	0d600893          	addi	a7,zero,214
   122e0:	00000513          	addi	a0,zero,0
   122e4:	00000073          	ecall
   122e8:	fff00613          	addi	a2,zero,-1
   122ec:	00050713          	addi	a4,a0,0
   122f0:	02c50a63          	beq	a0,a2,12324 <_sbrk+0x60>
   122f4:	00a6a023          	sw	a0,0(a3)
   122f8:	00e78533          	add	a0,a5,a4
   122fc:	0d600893          	addi	a7,zero,214
   12300:	00000073          	ecall
   12304:	0006a703          	lw	a4,0(a3)
   12308:	00e787b3          	add	a5,a5,a4
   1230c:	00f51c63          	bne	a0,a5,12324 <_sbrk+0x60>
   12310:	00c12083          	lw	ra,12(sp)
   12314:	00a6a023          	sw	a0,0(a3)
   12318:	00070513          	addi	a0,a4,0
   1231c:	01010113          	addi	sp,sp,16
   12320:	00008067          	jalr	zero,0(ra)
   12324:	060000ef          	jal	ra,12384 <__errno>
   12328:	00c12083          	lw	ra,12(sp)
   1232c:	00c00793          	addi	a5,zero,12
   12330:	00f52023          	sw	a5,0(a0)
   12334:	fff00513          	addi	a0,zero,-1
   12338:	01010113          	addi	sp,sp,16
   1233c:	00008067          	jalr	zero,0(ra)

00012340 <_write>:
   12340:	ff010113          	addi	sp,sp,-16
   12344:	00112623          	sw	ra,12(sp)
   12348:	00812423          	sw	s0,8(sp)
   1234c:	04000893          	addi	a7,zero,64
   12350:	00000073          	ecall
   12354:	00050413          	addi	s0,a0,0
   12358:	00054c63          	blt	a0,zero,12370 <_write+0x30>
   1235c:	00c12083          	lw	ra,12(sp)
   12360:	00040513          	addi	a0,s0,0
   12364:	00812403          	lw	s0,8(sp)
   12368:	01010113          	addi	sp,sp,16
   1236c:	00008067          	jalr	zero,0(ra)
   12370:	40800433          	sub	s0,zero,s0
   12374:	010000ef          	jal	ra,12384 <__errno>
   12378:	00852023          	sw	s0,0(a0)
   1237c:	fff00413          	addi	s0,zero,-1
   12380:	fddff06f          	jal	zero,1235c <_write+0x1c>

00012384 <__errno>:
   12384:	d3c1a503          	lw	a0,-708(gp) # 138dc <_impure_ptr>
   12388:	00008067          	jalr	zero,0(ra)
