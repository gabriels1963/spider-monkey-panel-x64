window.DefineScript('TrackInfo follows cursor');
include('docs/Flags.js');
include('docs/Helpers.js');

const font = gdi.Font('Segoe UI', 14);
const tfo = fb.TitleFormat('%title%[ - %artist%]');
let text = '';

on_item_focus_change();

function on_item_focus_change() {
	const handle = fb.GetFocusItem();

	if (handle)
		text = tfo.EvalWithMetadb(handle);
	else
		text = '';

	window.Repaint();
}

function on_playlist_switch() {
	//because on_item_focus_change isn't called when the user switches playlists
	//we must invoke it manually inside this callback
	on_item_focus_change();
}

function on_paint(gr) {
	gr.FillSolidRect(0, 0, window.Width, window.Height, RGB(255, 255, 255));

	if (text.length)
		gr.GdiDrawText(text, font, RGB(0, 0, 0), 0, 0, window.Width, window.Height, DT_VCENTER | DT_CENTER | DT_END_ELLIPSIS | DT_CALCRECT | DT_NOPREFIX);
}
