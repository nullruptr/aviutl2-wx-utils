#pragma once
#include <wx/wx.h>

namespace awx {

// DLL 内では wxIMPLEMENT_APP が使えないため、wx を手動で起動する。RegisterPlugin から呼ぶ。
inline bool StartWx()
{
    wxApp::SetInstance(new wxApp());
    int argc = 0;
    if (!wxEntryStart(argc, static_cast<wchar_t**>(nullptr)))
        return false;
    wxTheApp->CallOnInit();
    return true;
}

// StartWx が成功していたときだけ呼ぶ。UninitializePlugin から、フレームを Destroy した後に呼ぶ。
inline void StopWx() { wxEntryCleanup(); }

} // namespace awx
