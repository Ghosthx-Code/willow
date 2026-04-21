@init <py>
func print(str: *x) {
    printfl("%var%", *x) ?;
}
func input(str: *x) ? -> str {
    @return:
        inputfl("%var%", *x)
}
@endInit