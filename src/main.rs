mod musak_player;

use musak_player::{musak, MusakError};
use std::thread;

fn main() -> Result<(), MusakError> {
    let mut result = Result::Ok(());
    thread::scope(|s| {
        s.spawn(|| result = musak());
    });
    result
}
