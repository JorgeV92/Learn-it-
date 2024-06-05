// Some definitions presupposed by pandoc's typst output.
#let blockquote(body) = [
  #set text( size: 0.92em )
  #block(inset: (left: 1.5em, top: 0.2em, bottom: 0.2em))[#body]
]

#let horizontalrule = [
  #line(start: (25%,0%), end: (75%,0%))
]

#let endnote(num, contents) = [
  #stack(dir: ltr, spacing: 3pt, super[#num], contents)
]

#show terms: it => {
  it.children
    .map(child => [
      #strong[#child.term]
      #block(inset: (left: 1.5em, top: -0.4em))[#child.description]
      ])
    .join()
}

// Some quarto-specific definitions.

#show raw.where(block: true): block.with(
    fill: luma(230), 
    width: 100%, 
    inset: 8pt, 
    radius: 2pt
  )

#let block_with_new_content(old_block, new_content) = {
  let d = (:)
  let fields = old_block.fields()
  fields.remove("body")
  if fields.at("below", default: none) != none {
    // TODO: this is a hack because below is a "synthesized element"
    // according to the experts in the typst discord...
    fields.below = fields.below.amount
  }
  return block.with(..fields)(new_content)
}

#let empty(v) = {
  if type(v) == "string" {
    // two dollar signs here because we're technically inside
    // a Pandoc template :grimace:
    v.matches(regex("^\\s*$")).at(0, default: none) != none
  } else if type(v) == "content" {
    if v.at("text", default: none) != none {
      return empty(v.text)
    }
    for child in v.at("children", default: ()) {
      if not empty(child) {
        return false
      }
    }
    return true
  }

}

#show figure: it => {
  if type(it.kind) != "string" {
    return it
  }
  let kind_match = it.kind.matches(regex("^quarto-callout-(.*)")).at(0, default: none)
  if kind_match == none {
    return it
  }
  let kind = kind_match.captures.at(0, default: "other")
  kind = upper(kind.first()) + kind.slice(1)
  // now we pull apart the callout and reassemble it with the crossref name and counter

  // when we cleanup pandoc's emitted code to avoid spaces this will have to change
  let old_callout = it.body.children.at(1).body.children.at(1)
  let old_title_block = old_callout.body.children.at(0)
  let old_title = old_title_block.body.body.children.at(2)

  // TODO use custom separator if available
  let new_title = if empty(old_title) {
    [#kind #it.counter.display()]
  } else {
    [#kind #it.counter.display(): #old_title]
  }

  let new_title_block = block_with_new_content(
    old_title_block, 
    block_with_new_content(
      old_title_block.body, 
      old_title_block.body.body.children.at(0) +
      old_title_block.body.body.children.at(1) +
      new_title))

  block_with_new_content(old_callout,
    new_title_block +
    old_callout.body.children.at(1))
}

#show ref: it => locate(loc => {
  let target = query(it.target, loc).first()
  if it.at("supplement", default: none) == none {
    it
    return
  }

  let sup = it.supplement.text.matches(regex("^45127368-afa1-446a-820f-fc64c546b2c5%(.*)")).at(0, default: none)
  if sup != none {
    let parent_id = sup.captures.first()
    let parent_figure = query(label(parent_id), loc).first()
    let parent_location = parent_figure.location()

    let counters = numbering(
      parent_figure.at("numbering"), 
      ..parent_figure.at("counter").at(parent_location))
      
    let subcounter = numbering(
      target.at("numbering"),
      ..target.at("counter").at(target.location()))
    
    // NOTE there's a nonbreaking space in the block below
    link(target.location(), [#parent_figure.at("supplement") #counters#subcounter])
  } else {
    it
  }
})

// 2023-10-09: #fa-icon("fa-info") is not working, so we'll eval "#fa-info()" instead
#let callout(body: [], title: "Callout", background_color: rgb("#dddddd"), icon: none, icon_color: black) = {
  block(
    breakable: false, 
    fill: background_color, 
    stroke: (paint: icon_color, thickness: 0.5pt, cap: "round"), 
    width: 100%, 
    radius: 2pt,
    block(
      inset: 1pt,
      width: 100%, 
      below: 0pt, 
      block(
        fill: background_color, 
        width: 100%, 
        inset: 8pt)[#text(icon_color, weight: 900)[#icon] #title]) +
      block(
        inset: 1pt, 
        width: 100%, 
        block(fill: white, width: 100%, inset: 8pt, body)))
}



#let article(
  title: none,
  authors: none,
  date: none,
  abstract: none,
  cols: 1,
  margin: (x: 1.25in, y: 1.25in),
  paper: "us-letter",
  lang: "en",
  region: "US",
  font: (),
  fontsize: 11pt,
  sectionnumbering: none,
  toc: false,
  toc_title: none,
  toc_depth: none,
  doc,
) = {
  set page(
    paper: paper,
    margin: margin,
    numbering: "1",
  )
  set par(justify: true)
  set text(lang: lang,
           region: region,
           font: font,
           size: fontsize)
  set heading(numbering: sectionnumbering)

  if title != none {
    align(center)[#block(inset: 2em)[
      #text(weight: "bold", size: 1.5em)[#title]
    ]]
  }

  if authors != none {
    let count = authors.len()
    let ncols = calc.min(count, 3)
    grid(
      columns: (1fr,) * ncols,
      row-gutter: 1.5em,
      ..authors.map(author =>
          align(center)[
            #author.name \
            #author.affiliation \
            #author.email
          ]
      )
    )
  }

  if date != none {
    align(center)[#block(inset: 1em)[
      #date
    ]]
  }

  if abstract != none {
    block(inset: 2em)[
    #text(weight: "semibold")[Abstract] #h(1em) #abstract
    ]
  }

  if toc {
    let title = if toc_title == none {
      auto
    } else {
      toc_title
    }
    block(above: 0em, below: 2em)[
    #outline(
      title: toc_title,
      depth: toc_depth
    );
    ]
  }

  if cols == 1 {
    doc
  } else {
    columns(cols, doc)
  }
}
#show: doc => article(
  title: [Learn-it-],
  toc_title: [Table of contents],
  toc_depth: 3,
  cols: 1,
  doc,
)


This is a documentation of the process of learning and understanding algorithms and data structures, serving as a personal record of LeetCode questions. Most implementations will include more comments and descriptions than necessary. Initially, most implementations will be done in C++, but I will also work on an OCaml version to maintain my functional programming skills and continue growing my skill set with a meta-language. All resources will be credited and documented if I use solutions provided on the web, such as NeetCode.

== Arrays & Hashing
<arrays-hashing>
#figure(
align(center)[#table(
  columns: 3,
  align: (col, row) => (auto,auto,auto,).at(col),
  inset: 6pt,
  [Problem], [Ocaml], [C++],
  [#link("https://leetcode.com/problems/contains-duplicate/")[0217 - Contains Duplicate];],
  [],
  [],
)]
)

= JPMorgan
<jpmorgan>
#link(<Learn-it>)[\[back to top\]] | Problem | Difficulty | Solution | |:——————————————————————————————————————————–|:————-|:———————————————————————————————————————————————————————————————————————————————————————————–| | #link("https://leetcode.com/problems/reconstruct-original-digits-from-english/")[Reconstruct Original Digits from English] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_423.java")[Solution] | | #link("https://leetcode.com/problems/group-anagrams/")[Group Anagrams] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_49.java")[Solution] | | #link("https://leetcode.com/problems/maximum-subarray/")[Maximum Subarray] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_53.java")[Solution] | | #link("https://leetcode.com/problems/even-odd-tree/")[Even Odd Tree] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1609.java")[Solution] | | #link("https://leetcode.com/problems/best-time-to-buy-and-sell-stock/")[Best Time to Buy and Sell Stock] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_121.java")[Solution] | | #link("https://leetcode.com/problems/add-two-numbers/")[Add Two Numbers] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_2.java")[Solution] | | #link("https://leetcode.com/problems/two-sum/")[Two Sum] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1.java")[Java];, #link("https://github.com/fishercoder1534/Leetcode/blob/master/cpp/_1.cpp")[C++];, #link("https://github.com/fishercoder1534/Leetcode/blob/master/javascript/_1.js")[Javascript] | | #link("https://leetcode.com/problems/maximum-units-on-a-truck/")[Maximum Units on a Truck] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1710.java")[Solution] | | #link("https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/")[Minimum Value to Get Positive Step by Step Sum] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1413.java")[Solution] | | #link("https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/")[Maximum Number of Events That Can Be Attended] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1353.java")[Solution] | | #link("https://leetcode.com/problems/minimum-absolute-difference/")[Minimum Absolute Difference] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1200.java")[Solution] | | #link("https://leetcode.com/problems/intersection-of-two-arrays/")[Intersection of Two Arrays] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_349.java")[Solution] | | #link("https://leetcode.com/problems/counting-bits/")[Counting Bits] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_338.java")[Solution] | | #link("https://leetcode.com/problems/paint-fence/")[Paint Fence] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_276.java")[Solution] | | #link("https://leetcode.com/problems/longest-substring-without-repeating-characters/")[Longest Substring Without Repeating Characters] | Medium | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_3.java")[Solution];, #link("https://github.com/fishercoder1534/Leetcode/blob/master/cpp/_3.cpp")[C++] | | #link("https://leetcode.com/problems/determine-color-of-a-chessboard-square/")[Determine Color of a Chessboard Square] | Easy | #link("https://github.com/fishercoder1534/Leetcode/blob/master/src/main/java/com/fishercoder/solutions/_1812.java")[Solution] |
