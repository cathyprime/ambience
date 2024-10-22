mod data;
mod gui;
mod musak_player;

// use musak_player::{musak, MusakError};
// use gui::run_ui as start_ui;
// use std::thread;
// use std::sync::mpsc::channel;
use crate::data::Sounds;

fn main() /* -> Result<(), MusakError> */
{
    let sounds = Sounds::read_file("./example.csv");

    println!("{:#?}", sounds);
    // let (tx, rx) = channel();
    //
    // let handle = thread::spawn(move || musak(tx));
    // start_ui();
    // handle.join().unwrap();
    //
    // rx.recv().unwrap()
}
