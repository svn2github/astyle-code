// AStyleDlg.h
// Copyright (c) 2016 by Jim Pattee <jimp03@email.com>.
// This code is licensed under the MIT License.
// License.txt describes the conditions under which this software may be distributed.

#ifndef _ASTYLEDLG_H_
#define _ASTYLEDLG_H_

//-----------------------------------------------------------------------------
// headers
//-----------------------------------------------------------------------------

#include "AStyleDisplay.h"
#include "AStyleDlgBase.h"
#include "AStyleIFace.h"
#include "AStyleWx.h"
#include "SettingsDlg.h"

//-----------------------------------------------------------------------------
// definitions
//-----------------------------------------------------------------------------

// Define the page changed event for the selected book type.
// This must agree with the type in the generated AStyleDlgBase.h.
// May be a Choicebook, Listbook, Notebook, or Treebook.
// Since Notebook is always defined it must be the default.
// This fixes a problem with the event in Linux.
#ifndef wxBOOKCTRL_EVENT
	#if defined(EVT_CHOICEBOOK_PAGE_CHANGED)
		#define wxBOOKCTRL_EVENT wxChoicebookEvent
	#elif defined(EVT_LISTBOOK_PAGE_CHANGED)
		#define wxBOOKCTRL_EVENT wxListbookEvent
	#elif defined(EVT_TREEBOOK_PAGE_CHANGED)
		#define wxBOOKCTRL_EVENT wxTreebookEvent
	#else
		// this MUST be the default
		#define wxBOOKCTRL_EVENT wxNotebookEvent
	#endif
#endif	// wxBOOKCTRL_EVENT

//-----------------------------------------------------------------------------
// AStyleDlg Class
// The inherited AStyleDlgBase class is generated by wxFormBuilder.
//-----------------------------------------------------------------------------

class AStyleDlg: public AStyleDlgBase
{
public:
	AStyleDlg(ASFrame* frame, AStyleIFace* astyle, int page);
	~AStyleDlg();
	int  GetPage();

private:
	void AddAlignPointerData();
	void AddAlignReferenceData();
	void AddMaxCodeLengthData();
	void AddMaxInStatementData();
	void AddMinConditionalData();
	void AddPadMethodColonData();
	void EnableOrDisableTabLength();
	void GetFormatOptions(AStyleIFace* astyle);
	void GetIndentOptions(AStyleIFace* astyle);
	void GetModifierOptions(AStyleIFace* astyle);
	void GetOtherOptions(AStyleIFace* astyle);
	void GetPadOptions(AStyleIFace* astyle);
	void GetStyleOptions(AStyleIFace* astyle);
	void GetTabOptions(AStyleIFace* astyle);
	wxSize GetWxChoiceSize(const wxChoice* choice) const;
	wxSize GetWxSpinCtrlSize(const wxSpinCtrl* spin) const;
	void InitializeStaticBoxes(wxFont& defaultFont, wxStaticBoxSizer* sizer, wxStaticBoxSizer* previewSizer);
	void InitializeSTC(wxStyledTextCtrl* stc);
	void OnFormatClick(wxCommandEvent&);
	void OnIndentClick(wxCommandEvent&);
	void OnModifierClick(wxCommandEvent&);
	// May be a Choicebook, Listbook, Notebook, or Treebook.
	void OnNotebookPageChanged(wxBOOKCTRL_EVENT&);
	void OnOkClick(wxCommandEvent&);
	void OnOtherClick(wxCommandEvent&);
	void OnPadClick(wxCommandEvent&);
	void OnPreviewFocus(wxFocusEvent&);
	void OnResetAllClick(wxCommandEvent&);
	void OnSettingsClick(wxCommandEvent&);
	void OnStyleClick(wxCommandEvent&);
	void OnStyleMouseUp(wxMouseEvent&);
	void OnTabClick(wxCommandEvent&);
	void OnTabMouseUp(wxMouseEvent&);
	void SetFormatOptions();
	void SetIndentOptions();
	void SetModifierOptions();
	void SetOtherOptions();
	void SetPadOptions();
	void SetStyleOptions();
	void SetTabOptions();

private:

	AStyleIFace* m_astyle;		// pointer to the AStyleIFace object
	ASFrame* m_frame;			// pointer to the ASFrame object
	int m_page;					// currently selected dialog page
	AStyleDisplay* m_display;	// preview window display for AStyleDlg

	DECLARE_EVENT_TABLE()
};

#endif	// _ASTYLEDLG_H_
