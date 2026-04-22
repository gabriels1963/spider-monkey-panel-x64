window.DefineScript('LoadImageAsyncV2', { author: 'TheQwertiest' });

let g_img = null;

const load_image_async = async (metadb, art_id) =>
{
	const path = fb.ComponentPath + 'samples\\basic\\images\\post.jpg';
	g_img = await gdi.LoadImageAsyncV2(0, path);
	window.Repaint();
};

load_image_async();

function on_size() {
	ww = window.Width;
	wh = window.Height;
}

function on_paint(gr) {
	if (!g_img) {
		return;
	}

	let scale_w = ww / g_img.Width;
	let scale_h = wh / g_img.Height;
	let scale = Math.min(scale_w, scale_h);
	let pos_x = 0, pos_y = 0;

	if (scale_w < scale_h) {
		pos_y = (wh - g_img.Height * scale) / 2;
	}
	else if (scale_w > scale_h) {
		pos_x = (ww - g_img.Width * scale) / 2;
	}

	gr.DrawImage(g_img, pos_x, pos_y, g_img.Width * scale, g_img.Height * scale, 0, 0, g_img.Width, g_img.Height);
}
