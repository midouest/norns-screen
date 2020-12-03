const addon = require("../build/Release/norns-screen-native");

interface INornsScreenNative {
  deinit(): void;
  update(): void;
  save(): void;
  restore(): void;
  font_face(i: number): void;
  font_size(z: number): void;
  aa(s: number): void;
  level(z: number): void;
  line_width(w: number): void;
  line_cap(style: string): void;
  line_join(style: string): void;
  miter_limit(limit: number): void;
  move(x: number, y: number): void;
  line(x: number, y: number): void;
  move_rel(x: number, y: number): void;
  line_rel(x: number, y: number): void;
  curve(
    x1: number,
    y1: number,
    x2: number,
    y2: number,
    x3: number,
    y3: number
  ): void;
  curve_rel(
    dx1: number,
    dy1: number,
    dx2: number,
    dy2: number,
    dx3: number,
    dy3: number
  ): void;
  arc(x: number, y: number, r: number, a1: number, a2: number): void;
  rect(x: number, y: number, w: number, h: number): void;
  stroke(): void;
  fill(): void;
  text(s: string): void;
  clear(): void;
  close_path(): void;
  text_extents(s: string): void;
  export_png(s: string): void;
  display_png(filename: string, x: number, y: number): void;
  peek(x: number, y: number, w: number, h: number): Uint8Array;
  poke(x: number, y: number, w: number, h: number, buf: Uint8Array): void;
  rotate(r: number): void;
  translate(x: number, y: number): void;
  set_operator(i: number): void;
}

class NornsScreen {
  private _addonInstance: INornsScreenNative;

  constructor() {
    this._addonInstance = new addon.NornsScreen();
  }

  deinit(): void {
    this._addonInstance.deinit();
  }
  update(): void {
    this._addonInstance.update();
  }
  save(): void {
    this._addonInstance.save();
  }
  restore(): void {
    this._addonInstance.restore();
  }
  font_face(i: number): void {
    this._addonInstance.font_face(i);
  }
  font_size(z: number): void {
    this._addonInstance.font_size(z);
  }
  aa(s: number): void {
    this._addonInstance.aa(s);
  }
  level(z: number): void {
    this._addonInstance.level(z);
  }
  line_width(w: number): void {
    this._addonInstance.line_width(w);
  }
  line_cap(style: string): void {
    this._addonInstance.line_cap(style);
  }
  line_join(style: string): void {
    this._addonInstance.line_join(style);
  }
  miter_limit(limit: number): void {
    this._addonInstance.miter_limit(limit);
  }
  move(x: number, y: number): void {
    this._addonInstance.move(x, y);
  }
  line(x: number, y: number): void {
    this._addonInstance.line(x, y);
  }
  move_rel(x: number, y: number): void {
    this._addonInstance.move_rel(x, y);
  }
  line_rel(x: number, y: number): void {
    this._addonInstance.line_rel(x, y);
  }
  curve(
    x1: number,
    y1: number,
    x2: number,
    y2: number,
    x3: number,
    y3: number
  ): void {
    this._addonInstance.curve(x1, y1, x2, y2, x3, y3);
  }
  curve_rel(
    dx1: number,
    dy1: number,
    dx2: number,
    dy2: number,
    dx3: number,
    dy3: number
  ): void {
    this._addonInstance.curve_rel(dx1, dy1, dx2, dy2, dx3, dy3);
  }
  arc(x: number, y: number, r: number, a1: number, a2: number): void {
    this._addonInstance.arc(x, y, r, a1, a2);
  }
  rect(x: number, y: number, w: number, h: number): void {
    this._addonInstance.rect(x, y, w, h);
  }
  stroke(): void {
    this._addonInstance.stroke();
  }
  fill(): void {
    this._addonInstance.fill();
  }
  text(s: string): void {
    this._addonInstance.text(s);
  }
  clear(): void {
    this._addonInstance.clear();
  }
  close_path(): void {
    this._addonInstance.close_path();
  }
  text_extents(s: string): void {
    this._addonInstance.text_extents(s);
  }
  export_png(s: string): void {
    this._addonInstance.export_png(s);
  }
  display_png(filename: string, x: number, y: number): void {
    this._addonInstance.display_png(filename, x, y);
  }
  peek(x: number, y: number, w: number, h: number): Uint8Array {
    return this._addonInstance.peek(x, y, w, h);
  }
  poke(x: number, y: number, w: number, h: number, buf: Uint8Array): void {
    this._addonInstance.poke(x, y, w, h, buf);
  }
  rotate(r: number): void {
    this._addonInstance.rotate(r);
  }
  translate(x: number, y: number): void {
    this._addonInstance.translate(x, y);
  }
  set_operator(i: number): void {
    this._addonInstance.set_operator(i);
  }
}

export = NornsScreen;
