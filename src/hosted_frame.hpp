#pragma once
#include <wx/wx.h>
#include "dpi_patch.hpp"

namespace awx {

// register_window_client に渡す wx のフレームの基底クラス。
// wxBORDER_NONE (付けないと AviUtl2 側で MDI のような見た目になる) と、High DPI パッチを持つ。
class HostedFrame : public wxFrame {
public:
    HostedFrame()
        : wxFrame(nullptr, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
        , m_dpi_patch(*this)
    {
    }

protected:
    WXLRESULT MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam) override
    {
        if (m_dpi_patch.BeforeWndProc(msg))
            return 0;
        const WXLRESULT r = wxFrame::MSWWindowProc(msg, wParam, lParam);
        m_dpi_patch.AfterWndProc(msg);
        return r;
    }

private:
    AviUtl2DpiPatch m_dpi_patch;
};

} // namespace awx
