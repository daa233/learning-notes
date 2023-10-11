// Creating a String puts fixed-sized metadata on the stack and dynamically sized data,
// the actual string, on the heap
// ```bob
// Stack                             Heap
// .- - - - - - - - - - - - - -.     .- - - - - - - - - - - - - - - -.
// :                           :     :                               :
// :    s1                     :     :                               :
// :   +-----------+-------+   :     :   +----+----+----+----+----+  :
// :   | ptr       |   o---+---+-----+-->| H  | e  | l  | l  | o  |  :
// :   | len       |     5 |   :     :   +----+----+----+----+----+  :
// :   | capacity  |     5 |   :     :                               :
// :   +-----------+-------+   :     :                               :
// :                           :     `- - - - - - - - - - - - - - - -'
// `- - - - - - - - - - - - - -'
// ```
pub fn stack_and_heap() {
    let s1 = String::from("Hello");
    println!("s1: {s1}");
}
