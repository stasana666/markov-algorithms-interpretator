#!/usr/bin/env python3

alphabet = list(map(str, range(10)))
output_alphabet = alphabet + ["_"]

terms = set()

def rule(src, dst, delimiter=" -> "):
    def processTerm(term):
        terms.add(term)
        if term in output_alphabet or term == "":
            return term
        return f"_{term}_"

    srcTerms = list(map(processTerm, src.split()))
    dstTerms = list(map(processTerm, dst.split()))

    return " ".join(srcTerms) + delimiter + " ".join(dstTerms)


def main():
    create_start_and_end = rule("", "start end")

    init_end_position = "\n".join([
        rule(f"end {i}", f"{i} end") for i in alphabet
    ])

    create_current = rule("start", "start current")

    remove_first_zero = "\n".join([
        rule(f"numberDelimiter 0 {i}", f"numberDelimiter {i}") for i in alphabet
    ])

    process_copy = "\n".join([
        rule("current", "startCopy"),
        rule("startCopy", "awaitCopy copyMoveRight"),
    ] + [
        rule(f"copyMoveRight {i}", f"{i} copyMoveRight") for i in alphabet
    ] + [
        rule("copyMoveRight end", "copyMoveLeft copyDelimiter end")
    ] + [
        rule(f"{i} copyMoveLeft", f"copyMoveLeft {i} carry[{i}]") for i in alphabet
    ] + [
        rule(f"carry[{i}] {j}", f"{j} carry[{i}]")
        for i in alphabet
        for j in alphabet
    ] + [
        rule(f"carry[{i}] copyDelimiter", f"copyDelimiter {i}") for i in alphabet
    ] + [
        rule("awaitCopy copyMoveLeft", ""),
        rule("copyDelimiter", "numberDelimiter startSub")
    ])

    process_substruction = "\n".join([
        rule("startSub", "awaitSub subMoveRight"),
    ] + [
        rule(f"subMoveRight {i}", f"{i} subMoveRight") for i in alphabet
    ] + [
        rule("subMoveRight end", "minus " * 7 + "end"),
        rule("0 minus", "minus 9")
    ] + [
        rule(f"{i} minus", f"{str(int(i) - 1)}") for i in alphabet[1:]
    ] + [
        rule("awaitSub minus", "finish"),
        rule("awaitSub", "current")
    ])

    finish = "\n".join([
        rule("finish", "finishMoveLeft terminate finishMoveRight"),
        rule("start finishMoveLeft", ""),
        rule("finishMoveRight end", ""),
        rule("numberDelimiter finishMoveLeft", "finishMoveLeft _")
    ] + [
        rule(f"{i} finishMoveLeft", f"finishMoveLeft {i}") for i in terms
    ] + [
        rule(f"finishMoveRight {i}", f"finishMoveRight") for i in terms
    ] + [
        rule("terminate", "", "=>")
    ])

    rules = [
        init_end_position,
        finish,
        remove_first_zero,
        process_copy,
        process_substruction,
        create_current,
        create_start_and_end
    ]

    print("\n".join(rules))


if __name__ == "__main__":
    main()
