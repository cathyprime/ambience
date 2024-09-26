mod musak_player;
mod gui;

use musak_player::{musak, MusakError};
use gui::run_ui as start_ui;
use std::thread;
use std::sync::mpsc::channel;

fn main() -> Result<(), MusakError> {
    let (tx, rx) = channel();

    let handle = thread::spawn(move || musak(tx));
    start_ui();
    handle.join().unwrap();

    rx.recv().unwrap()
}
