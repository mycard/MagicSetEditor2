//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2006 Twan van Laarhoven                           |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#ifndef HEADER_GUI_CONTROL_CARD_VIEWER
#define HEADER_GUI_CONTROL_CARD_VIEWER

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <render/card/viewer.hpp>

// ----------------------------------------------------------------------------- : Events

/// Event that indicates the size of a CardViewer has changed
DECLARE_EVENT_TYPE(EVENT_SIZE_CHANGE, <not used>)
/// Handle EVENT_SIZE_CHANGE events
#define EVT_SIZE_CHANGE(id, handler) EVT_COMMAND(id, EVENT_SIZE_CHANGE, handler)

// ----------------------------------------------------------------------------- : CardViewer

/// A control to view a single card
class CardViewer : public wxControl, public DataViewer {
  public:
	CardViewer(Window* parent, int id, long style = 0);
	
	/// Get a dc to draw on the card outside onPaint	
	/** May NOT be called while in onPaint/draw */
	shared_ptr<DC> overdrawDC();
	
  protected:
	/// Return the desired size of control
	virtual wxSize DoGetBestSize() const;
	
	virtual void onChange();
	virtual void onChangeSize();
	
  private:
	DECLARE_EVENT_TABLE();
	
	void onPaint(wxPaintEvent&);
	
	Bitmap buffer;     ///< Off-screen buffer we draw to
	bool   up_to_date; ///< Is the buffer up to date?
	
	class OverdrawDC;
};

// ----------------------------------------------------------------------------- : EOF
#endif
