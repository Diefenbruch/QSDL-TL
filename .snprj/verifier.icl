 1b                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          �0��H�t������`pTT�04tT��0�����Pl�x��0Lp,L��$��������h|�H\|(<<�����������0���ptPX�4@�$p�\		if {$val != ""} {
			foreach win $val {
				#create window
				incr tkeWinNumber
				set nwin ".multisymbr-$tkeWinNumber"
				SymBr& $nwin \
					-x [lindex $win 1] \
					-y [lindex $win 2] \
					-width [lindex $win 3] \
					-height [lindex $win 4] \
					-restore 1; #don't exec filter
				wm geometry $nwin [lindex $win 5]
				$nwin Restore [lindex $win 6]; #restore old retriever status
			}
		}
	}
	
	protected symbr ""
	protected topw "."
	protected Toolbar ""
	protected SymbolsFilter ""
	protected Statusbar ""
	#protected Reuse ""
	
	public restore 0
	public x ""
	public y ""
	public width  45
	public height 30
}

   % inde    heri Y��plev [�0		
	    tructor {{config ""}} {
		global sn_options
		Toplevel&@@constructor -class SymBr
		set topw $this
		set symbr $this.symbr
		
		$this withdraw
		wm protocol $this WM_DELETE_WINDOW "$this windows_close dummy"
		if {$x != ""} {
			wm geometry $this [expr int($width)]x[expr int($height)]+$x+$y
		}
		
		set Toolbar $this.exp
		set Statusbar $this.msg
		#set Reuse $this.msg.reuse
		
		AddMenu
		AddToolbar
		AddStatusbar
		
		Retr& $symbr  -symbols ""  -symbols_filter ""  -menu "$this.menu"  -toolbar "$Toolbar"  -mesg_area ""  -height $height  -width $width  -mode symbr  -restore $restore  -selectcommand "$this handle_select"
		pack $symbr -expand y -fill both -side left

		$symbr SetTitle
		
		after idle "$this deiconify"
		
		$symbr Focus
		
		#call user function
		catch {sn_rc_symbolbrowser $this $this.menu}
	}
	destructor {
		foreach v [@@info globals "$this-*"] {
			catch {uplevel #0 unset $v}
		}
	}
	method config {config} {
	}
	method AddToolbar {} {
		set exp $Toolbar
		frame $Toolbar -relief groove -border 2
		pack $Toolbar -side top -fill x
		
		#Hide project
		#button $exp.hide -image mug_image #	-command "sn_hide_show_project withdraw"
		#balloon_bind_info $exp.hide [get_indep String INFOHide]
		#pack $exp.hide -side left
	
		#Hierarchy
		button $exp.tree  -image tree_image -command "watch y;$this run_ctree;watch n" -state disabled
		bind_history $exp.tree tree
		balloon_bind_info $exp.tree [get_indep String INFOHierarchy]
		pack $exp.tree -side left
		
		#Class
		button $exp.class  -image watch_image -command "watch y;$this run_class;watch n" -state disabled
		bind_history $exp.class browse
		balloon_bind_info $exp.class [get_indep String INFOStartClassBrw]
		pack $exp.class -side left
		
		#Xref
		button $exp.xref  -image crossref_image -command "$this run_xref"  -state disabled
		bind_history $exp.xref xref
		balloon_bind_info $exp.xref [get_indep String StartXRefINFO]
		pack $exp.xref -side left
		
		#Include
		button $exp.inc  -image include_image -command "watch y $topw; $this run_include; watch n $topw"  -state disabled
		balloon_bind_info $exp.inc [get_indep String IncludesINFO]
		pack $exp.inc -side left
		
		pack [frame $exp.space -width 7] -side left
	}
	method AddStatusbar {} {
		global sn_options
		
		frame $Statusbar
		
		#global $Statusbar.reusable
		#if {![@@info exists $Statusbar.reusable]} {
		#	uplevel #0 "set $Statusbar.reusable 1"
		#}
		#use the option flag
		#checkbutton $Reuse  #		-relief groove #		-text [get_indep String Reuse]  #		-variable $Statusbar.reusable  #		-font $sn_options(layout_font)
		#balloon_bind_info $Reuse [get_indep String ReusableINFO]
		#pack $Reuse -side left
		#uplevel #0 "set $Statusbar.reusable \$sn_options(window_reuse)"
		
		pack [label $Statusbar.msg  -font $sn_options(layout_font)  -relief groove  -bd 2  -anchor w  -textvar $this.msg] -expand y -fill both -side left
		pack $Statusbar -side bottom -fill x
	}
	
	method handle_select {{scope ""} {sym ""} {cls ""} {file ""} {from ""} {type ""} {prm ""} {to ""} {always 1}} {
		if {$scope == "cl"} {
			set cls $sym
		}
		if {$cls != ""} {
			set class_state normal
		} else {
			set class_state disabled
		}
		if {$file != ""} {
			set inc_state normal
		} else {
			set inc_state disabled
		}
		set xref_state [tool_Exists xref]
		if {$sym == "" && $xref_state == "normal"} {
			set xref_state disabled
		}
		$Toolbar.tree  config -state $class_state
		$Toolbar.class config -state $class_state
		$Toolbar.inc   config -state $inc_state
		$Toolbar.xref  config -state $xref_state
	}
	
	method run_tool {tool {scope ""} {sym ""} {cls ""} {file ""} {from ""} {type ""} {prm ""} {to ""} {always 1}} {
		switch -- $tool {
			"inc" {
				sn_include $file
			}
			"xref" {
				if {$from == ""} {
					set from -1
				}
				if {$to == ""} {
					set to -1
				}
				if {$cls != ""} {
					set sym "$cls\:\:${sym}($scope)"
				} else {
					set sym ${sym}($scope)
				}
				sn_xref both [string trim $sym] $type $file $from $to $prm
			}
			"class" {
				#go direct to the member if something given
				sn_classbrowser "" [list $scope $sym $cls $file $from $type $prm $to]
			}
			"ctree" {
				if {$scope == "cl"} {
					set cls $sym
				}
				sn_classtree $cls
			}
			default {
				bell
			}
		}
	}
	
	method run_ctree {} {
		eval run       TLMain.cpp . #        TL.l . # ru       lex.yy.c . # n_       TL.tab.h . # ec       TL.tab.c . # _i       TL.y . #  r       TLTemplates.cpp . # ]
	       TLIndetVerify.cpp . # l       TLBuechi.cpp . # ec       TLStateList.cpp . #  it       TLState.cpp . # #ex       TLParserHelp.cpp . # wi       TLParser.cpp . #  {       TLNode.cpp . #        TLHelp.cpp . #        TLFormulaZ_OPER.cpp . # his       TLFormulaWAITFOR.cpp . # se       TLFormulaV_OPER.cpp . # pro       TLFormulaUnary.cpp . #        TLFormulaUNTIL.cpp . #        TLFormulaTRUE.cpp . # d       TLFormulaSet.cpp . #  p       TLFormulaOR.cpp . # 	
	       TLFormulaNOT.cpp . # -t       TLFormulaNEXTTIME.cpp . # #       TLFormulaIMPLIES.cpp . # f        TLFormulaFALSE.cpp . #        TLFormulaEQUIVALENT.cpp . # abe       TLFormulaEVENTUALLY.cpp . # $m.       TLFormulaBinary.cpp . # dit       TLFormulaAtomic_NOT.cpp . # ddP       TLFormulaAtomic.cpp . # 	
	       TLFormulaAND.cpp . # lo       TLFormulaALWAYS.cpp . # -co       TLFormula.cpp . # $       TLStateList.inl.h . # n       TLState.inl.h . #         TLIndetVerify.inl.h . # cel       TLFormulaZ_OPER.inl.h . # n       TLFormulaWAITFOR.inl.h . #        TLFormulaV_OPER.inl.h . # m       TLFormulaUnary.inl.h . # 		       TLDebug.cpp . # ###       TLFormulaUNTIL.inl.h . # st       TLFormulaTRUE.inl.h . # 

	       TLFormulaSet.inl.h . #        TLFormulaOR.inl.h . #         TLFormulaNOT.inl.h . #        TLFormulaNEXTTIME.inl.h . # kbu       TLFormulaIMPLIES.inl.h . #        TLFormulaFALSE.inl.h . # os       TLFormulaEQUIVALENT.inl.h . # s       TLFormulaEVENTUALLY.inl.h . # "       TLFormulaBinary.inl.h . # e       TLFormulaAtomic_NOT.inl.h . # d       TLFormulaAtomic.inl.h . # o       TLFormulaAND.inl.h . #        TLFormulaALWAYS.inl.h . #         TLConfig.h . #        TLNode.inl.h . #  p       TLFormula.inl.h . # tat       TLBuechi.inl.h . #        TLStack.tmpl.h . #        TLStateList.h . #         TLState.h . # i       TLParserHelp.h . #        TLParser.h . #        TLNode.h . # r        TLLexer.h . # e       TLIndetVerify.h . # n         TLFormulaZ_OPER.h . #         TLFormulaWAITFOR.h . #        TLFormulaV_OPER.h . # o       TLFormulaUnary.h . # om       TLFormulaUNTIL.h . # ex       TLFormulaTRUE.h . # ect       TLFormulaSet.h . #        TLFormulaOR.h . # m       TLFormulaNOT.h . #        TLFormulaNEXTTIME.h . # und       TLHelp.h . # Pr       TLFormulaIMPLIES.h . #        TLFormulaFALSE.h . # re       TLFormulaEQUIVALENT.h . # 
       TLFormulaEVENTUALLY.h . # o       TLFormulaBinary.h . # s       TLFormulaAtomic_NOT.h . # _       TLFormulaAtomic.h . # o       TLFormulaAND.h . #        TLFormulaALWAYS.h . # c       TLFormula.h . # nu        TLDebug.h . # r       TLBuechiHelp.h . #        TLBuechi.h . #        TLStack.h . # n       Makefile . # $m       TL.h . # 
	